import concurrent.futures
import multiprocessing
import os
import platform
import shlex
import sys
import subprocess
import unittest
from unittest.mock import patch, call
from CloudundancyPyUtils import Process, UnitTester, Random

testNames = [
'run_RunsProcess_ReturnsStdOutStdErrAndReturnCode_test',
'fail_fast_run_CallsProcessAndGetExitCode_SysExitsWithExitCodeIfRunReturnsNonZero_test',
'run_and_get_exit_code_RunsProcess_ReturnsExitCode_test',
'run_and_get_exit_code_RunsProcess_ProcessRaisesAnException_PrintsException_Exits1_test',
'cross_platform_subprocess_call_CallsSubprocessCallOnWindows_CallsShlexSubprocessCallOnNotWindows_test',
'append_args_AppendsSpaceThenArgsIfArgsNotEmpty_testCases',
'run_parallel_processpoolexecutor_CallsProcessPoolExecutorMap_Returns1IfAnyExitCodesNon0_test',
'bytes_to_utf8_ReturnsBytesDecodedToUtf8_test'
]

class ProcessTests(unittest.TestCase):
   def setUp(self):
      self.configuration = Random.string()
      self.projectName = Random.string()
      self.appendArgsReturnValue = Random.string()
      self.command = Random.string()
      self.shlexedCommand = Random.string()
      self.currentWorkingDirectory = Random.string()
      self.ExpectedPylintcommand = 'pylint --rcfile=.pylintrc --init-hook=\"sys.path.append(\'.\')\" '

   @patch('shlex.split', spec_set=True)
   @patch('subprocess.run', spec_set=True)
   @patch('CloudundancyPyUtils.Process.bytes_to_utf8', spec_set=True)
   def run_RunsProcess_ReturnsStdOutStdErrAndReturnCode_test(self, _1, _2, _3):
      shlex.split.return_value = self.shlexedCommand
      args = [Random.string(), Random.string()]
      returncode = Random.integer()
      stdoutBytes = bytes(Random.string(), 'utf-8')
      stderrBytes = bytes(Random.string(), 'utf-8')
      subprocessRunReturnValue = subprocess.CompletedProcess(args, returncode, stdoutBytes, stderrBytes)
      subprocess.run.return_value = subprocessRunReturnValue
      stdoutUtf8 = Random.string()
      stderrUtf8 = Random.string()
      Process.bytes_to_utf8.side_effect = [stdoutUtf8, stderrUtf8]
      #
      completedProcess = Process.run(self.command)
      #
      shlex.split.assert_called_once_with(self.command)
      subprocess.run.assert_called_once_with(self.shlexedCommand, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
      self.assertEqual(2, len(Process.bytes_to_utf8.call_args_list))
      Process.bytes_to_utf8.assert_has_calls([call(stdoutBytes), call(stderrBytes)])
      expectedReturnValue = subprocess.CompletedProcess(args, returncode, stdoutUtf8, stderrUtf8)
      self.assertEqual(expectedReturnValue.args, completedProcess.args)
      self.assertEqual(expectedReturnValue.returncode, completedProcess.returncode)
      self.assertEqual(expectedReturnValue.stdout, completedProcess.stdout)
      self.assertEqual(expectedReturnValue.stderr, completedProcess.stderr)

   def fail_fast_run_CallsProcessAndGetExitCode_SysExitsWithExitCodeIfRunReturnsNonZero_test(self):
      @patch('CloudundancyPyUtils.Process.run_and_get_exit_code', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(exitCode, expectPrintCommandFailedAndExit, _1, printMock, _3):
         with self.subTest(f'{exitCode, expectPrintCommandFailedAndExit}'):
            Process.run_and_get_exit_code.return_value = exitCode
            #
            Process.fail_fast_run(self.command)
            #
            Process.run_and_get_exit_code.assert_called_once_with(self.command)
            if expectPrintCommandFailedAndExit:
               expectedSingleQuotedCommand = f'\'{self.command}\''
               printMock.assert_called_once_with('Command', expectedSingleQuotedCommand, 'failed with exit code', exitCode)
               sys.exit.assert_called_once_with(exitCode)
            else:
               sys.exit.assert_not_called()
      testcase(-1, True)
      testcase(0, False)
      testcase(1, True)

   @patch('os.getcwd', spec_set=True)
   @patch('builtins.print', spec_set=True)
   @patch('CloudundancyPyUtils.Process.cross_platform_subprocess_call', spec_set=True)
   def run_and_get_exit_code_RunsProcess_ReturnsExitCode_test(self, _1, printMock, _3):
      os.getcwd.return_value = self.currentWorkingDirectory
      subprocessReturnValue = Random.integer()
      Process.cross_platform_subprocess_call.return_value = subprocessReturnValue
      #
      exitCode = Process.run_and_get_exit_code(self.command)
      #
      os.getcwd.assert_called_once_with()
      printMock.assert_called_once_with('Running', f'\'{self.command}\'', 'from', self.currentWorkingDirectory)
      Process.cross_platform_subprocess_call.assert_called_once_with(self.command)
      self.assertEqual(subprocessReturnValue, exitCode)

   @patch('os.getcwd', spec_set=True)
   @patch('builtins.print', spec_set=True)
   @patch('CloudundancyPyUtils.Process.cross_platform_subprocess_call', spec_set=True)
   @patch('sys.exit', spec_set=True)
   def run_and_get_exit_code_RunsProcess_ProcessRaisesAnException_PrintsException_Exits1_test(self, _1, _2, printMock, _4):
      os.getcwd.return_value = self.currentWorkingDirectory
      exceptionMessage = Random.string()
      Process.cross_platform_subprocess_call.side_effect = FileNotFoundError(exceptionMessage)
      #
      Process.run_and_get_exit_code(self.command)
      #
      os.getcwd.assert_called_once_with()
      Process.cross_platform_subprocess_call.assert_called_once_with(self.command)
      self.assertEqual(2, len(printMock.call_args_list))
      printMock.assert_has_calls([
         call('Running', f'\'{self.command}\'', 'from', self.currentWorkingDirectory),
         call(exceptionMessage)])
      sys.exit.assert_called_once_with(1)

   def cross_platform_subprocess_call_CallsSubprocessCallOnWindows_CallsShlexSubprocessCallOnNotWindows_test(self):
      @patch('platform.system', spec_set=True)
      @patch('shlex.split', spec_set=True)
      @patch('subprocess.call', spec_set=True)
      def testcase(platformSystem, expectShlex, _1, _2, _3):
         with self.subTest(f'{platformSystem, expectShlex}'):
            platform.system.return_value = platformSystem
            if expectShlex:
               shlex.split.return_value = self.shlexedCommand
            subprocessCallReturnValue = 1
            subprocess.call.return_value = subprocessCallReturnValue
            #
            exitCode = Process.cross_platform_subprocess_call(self.command)
            #
            platform.system.assert_called_once_with()
            if expectShlex:
               subprocess.call.assert_called_once_with(self.shlexedCommand)
            else:
               subprocess.call.assert_called_once_with(self.command)
            self.assertEqual(subprocessCallReturnValue, exitCode)
      testcase('Windows', False)
      testcase('windows', False)
      testcase('Linux', True)
      testcase('OSX', True)

   def append_args_AppendsSpaceThenArgsIfArgsNotEmpty_testCases(self):
      def testcase(expectedReturnValue, args):
         with self.subTest(f'{expectedReturnValue, args}'):
            returnValue = Process.append_args('ExePath', args)
            self.assertEqual(expectedReturnValue, returnValue)
      testcase('ExePath', '')
      testcase('ExePath  ', ' ')
      testcase('ExePath arg1', 'arg1')
      testcase('ExePath arg1 arg2', 'arg1 arg2')

   def run_parallel_processpoolexecutor_CallsProcessPoolExecutorMap_Returns1IfAnyExitCodesNon0_test(self):
      class ProcessPoolExecutorMock:
         def __init__(self):
            self.map_numberOfCalls = 0
            self.map_funcArg = None
            self.map_iterableArg = None
            self.map_returnValue = None
            self.shutdown_numberOfCalls = 0
            self.shutdown_waitArg = None

         def map(self, func, iterable):
            self.map_numberOfCalls = self.map_numberOfCalls + 1
            self.map_funcArg = func
            self.map_iterableArg = iterable
            return self.map_returnValue

         def shutdown(self, wait):
            self.shutdown_numberOfCalls = self.shutdown_numberOfCalls + 1
            self.shutdown_waitArg = wait

         def assert_map_called_once_with(self, expectedFunc, expectedIterable):
            assert self.map_numberOfCalls == 1
            assert expectedFunc, self.map_funcArg
            assert expectedIterable, self.map_iterableArg

         def assert_shutdown_called_once_with(self, expectedWait):
            assert 1, self.numberOfShutdownCalls
            assert expectedWait, self.shutdown_waitArg

      @patch('concurrent.futures.ProcessPoolExecutor', spec_set=True)
      @patch('multiprocessing.cpu_count', spec_set=True)
      def testcase(expectedReturnValue, exitCodes, _1, _2):
         with self.subTest(f'{expectedReturnValue, exitCodes}'):
            cpuCount = Random.integer()
            multiprocessing.cpu_count.return_value = cpuCount
            Iterable = ['a', 'b', 'c']
            processPoolExecutorMock = ProcessPoolExecutorMock()
            processPoolExecutorMock.map_returnValue = exitCodes
            concurrent.futures.ProcessPoolExecutor.return_value = processPoolExecutorMock
            #
            allCommandsExited0 = Process.run_parallel_processpoolexecutor(len, Iterable)
            #
            multiprocessing.cpu_count.assert_called_once_with()
            concurrent.futures.ProcessPoolExecutor.assert_called_once_with(cpuCount)
            processPoolExecutorMock.assert_map_called_once_with(len, Iterable)
            processPoolExecutorMock.assert_shutdown_called_once_with(True)
            self.assertEqual(expectedReturnValue, allCommandsExited0)
      testcase(False, [-1])
      testcase(True, [0])
      testcase(True, [0, 0])
      testcase(False, [1])
      testcase(False, [2])
      testcase(False, [1, 0])
      testcase(False, [0, 1])
      testcase(False, [0, 1, 0])

   def bytes_to_utf8_ReturnsBytesDecodedToUtf8_test(self):
      self.assertEqual('', Process.bytes_to_utf8(b''))
      self.assertEqual('\r\n', Process.bytes_to_utf8(b'\r\n'))

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(ProcessTests, testNames)
