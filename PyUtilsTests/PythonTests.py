import glob
import os
import platform
import sys
import unittest
from unittest.mock import call, patch
from PyUtils import Python, Process, UnitTester, Random

testNames = [
'pylint_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders_test',
'pylint_all_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential_test',
'flake8_all_RunsFlake8WithFlake8Config_test',
'run_all_with_coverage_RunsCoverage_RunsReport_RunsHtml_RunsXml_ExitsWithReportExitCode_test'
]

class PythonTests(unittest.TestCase):

   ExpectedPylintCommand = 'pylint --rcfile=.pylintrc --score=n --init-hook=\"sys.path.append(\'.\')\" '

   @patch('PyUtils.Process.run_and_get_exit_code', spec_set=True)
   def pylint_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders_test(self, _1):
      pylintExitCode = Random.integer()
      Process.run_and_get_exit_code.return_value = pylintExitCode
      pythonFilePath = Random.string()
      #
      pylintExitCode = Python.pylint_file(pythonFilePath)
      #
      Process.run_and_get_exit_code.assert_called_once_with(self.ExpectedPylintCommand + pythonFilePath)
      self.assertEqual(pylintExitCode, pylintExitCode)

   def pylint_all_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential_test(self):
      @patch('glob.glob', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('PyUtils.Process.run_parallel_ProcessPoolExecutor', spec_set=True)
      @patch('PyUtils.Process.run_foreach', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(platformSystem, expectedMapParallel, allPylintsSucceeded, expectSysExit1, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem, expectedMapParallel, allPylintsSucceeded, expectSysExit1}'):
            PyFilePaths = [Random.string(), Random.string()]
            glob.glob.return_value = PyFilePaths
            platform.system.return_value = platformSystem
            if expectedMapParallel:
               Process.run_parallel_ProcessPoolExecutor.return_value = allPylintsSucceeded
            else:
               Process.run_foreach.return_value = allPylintsSucceeded
            #
            Python.pylint_all()
            #
            glob.glob.assert_called_once_with('**/*.py', recursive=True)
            platform.system.assert_called_once_with()
            if expectedMapParallel:
               Process.run_parallel_ProcessPoolExecutor.assert_called_once_with(Python.pylint_file, PyFilePaths)
               Process.run_foreach.assert_not_called()
            else:
               Process.run_parallel_ProcessPoolExecutor.assert_not_called()
               Process.run_foreach.assert_called_once_with(self.ExpectedPylintCommand, PyFilePaths)
            if expectSysExit1:
               sys.exit.assert_called_once_with(1)
            else:
               sys.exit.assert_not_called()
      testcase('Linux', True, True, False)
      testcase('Windows', False, False, True)
      testcase('windows', True, False, True)

   @patch('PyUtils.Process.fail_fast_run', spec_set=True)
   def flake8_all_RunsFlake8WithFlake8Config_test(self, _1):
      #
      Python.flake8_all()
      #
      expectedFlake8Command = 'flake8 --config=.flake8 --show-source --benchmark'
      Process.fail_fast_run.assert_called_once_with(expectedFlake8Command)

   def run_all_with_coverage_RunsCoverage_RunsReport_RunsHtml_RunsXml_ExitsWithReportExitCode_test(self):
      @patch('builtins.print', spec_set=True)
      @patch('os.getcwd', spec_set=True)
      @patch('PyUtils.Process.fail_fast_run', spec_set=True)
      @patch('PyUtils.Process.run_and_get_exit_code', spec_set=True)
      @patch('sys.exit', spec_set=True)
      @patch('builtins.print', spec_set=True)
      def testcase(reportExitCode, expectedConcludingPrint, _1, _2, _3, _4, _5, _6):
         currentWorkingDirectory = Random.string()
         os.getcwd.return_value = currentWorkingDirectory
         Process.run_and_get_exit_code.return_value = reportExitCode
         omitPattern = Random.string()
         #
         Python.run_all_with_coverage(omitPattern)
         #
         self.assertEqual(2, len(print.call_args_list))
         print.assert_has_calls([call('Running RunAll.py with coverage from', currentWorkingDirectory)])
         Process.run_and_get_exit_code.assert_called_once_with(
            f'coverage3 report --omit="{omitPattern}" --fail-under=100 --show-missing')
         self.assertEqual(3, len(Process.fail_fast_run.call_args_list))
         Process.fail_fast_run.assert_has_calls([
            call('coverage3 run --branch RunAll.py'),
            call('coverage3 html'),
            call(f'coverage3 xml --omit="{omitPattern}"')])
         print.assert_has_calls([call(expectedConcludingPrint)])
         sys.exit.assert_called_once_with(reportExitCode)
      testcase(-1, 'Failure. Coverage is less than 100%.')
      testcase(0, 'Success. Coverage is 100%.')
      testcase(1, 'Failure. Coverage is less than 100%.')
      testcase(2, 'Failure. Coverage is less than 100%.')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(PythonTests, testNames)
