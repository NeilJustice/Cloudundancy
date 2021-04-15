import glob
import os
import platform
import sys
import unittest
from unittest.mock import call, patch
from CloudundancyPyUtils import Process, Python
from CloudundancyPyUtilsTests import Random, UnitTester

testNames = [
'run_flake8_RunsFlake8WithFlake8Config_test',
'run_mypy_RunsMypyDotWithIgnoreMissingImports_test',
'run_pylint_on_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders_test',
'run_pylint_on_all_files_in_parallel_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential_test',
'run_all_with_coverage_RunsCoverage_RunsReport_RunsHtml_RunsXml_ExitsWithReportExitCode_test'
]

class PythonTests(unittest.TestCase):

   ExpectedPylintCommand = 'pylint --rcfile=.pylintrc --score=n --init-hook=\"sys.path.append(\'.\')\" '

   @staticmethod
   @patch('CloudundancyPyUtils.Process.fail_fast_run', spec_set=True)
   def run_flake8_RunsFlake8WithFlake8Config_test(_1):
      #
      Python.run_flake8()
      #
      expectedFlake8Command = 'flake8 --config=.flake8 --show-source --benchmark'
      Process.fail_fast_run.assert_called_once_with(expectedFlake8Command)

   @staticmethod
   @patch('CloudundancyPyUtils.Process.fail_fast_run', spec_set=True)
   def run_mypy_RunsMypyDotWithIgnoreMissingImports_test(_1):
      #
      Python.run_mypy()
      #
      expectedMypyCommand = 'mypy . --ignore-missing-imports --disallow-untyped-calls --disallow-incomplete-defs'
      Process.fail_fast_run(expectedMypyCommand)

   @patch('CloudundancyPyUtils.Process.run_and_get_exit_code', spec_set=True)
   def run_pylint_on_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders_test(self, _1):
      pylintExitCode = Random.integer()
      Process.run_and_get_exit_code.return_value = pylintExitCode
      pythonFilePath = Random.string()
      #
      pylintExitCode = Python.run_pylint_on_file(pythonFilePath)
      #
      Process.run_and_get_exit_code.assert_called_once_with(PythonTests.ExpectedPylintCommand + pythonFilePath)
      self.assertEqual(pylintExitCode, pylintExitCode)

   def run_pylint_on_all_files_in_parallel_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential_test(self):
      @patch('glob.glob', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('CloudundancyPyUtils.Process.run_parallel_processpoolexecutor', spec_set=True)
      @patch('CloudundancyPyUtils.Process.run_parallel_processthread', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(platformSystem, expectedMapParallel, allPylintProcessesSucceeded, expectSysExit1, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem, expectedMapParallel, allPylintProcessesSucceeded, expectSysExit1}'):
            PyFilePaths = [Random.string(), Random.string()]
            glob.glob.return_value = PyFilePaths
            platform.system.return_value = platformSystem
            if expectedMapParallel:
               Process.run_parallel_processpoolexecutor.return_value = allPylintProcessesSucceeded
            else:
               Process.run_parallel_processthread.return_value = allPylintProcessesSucceeded
            #
            Python.run_pylint_on_all_files_in_parallel()
            #
            glob.glob.assert_called_once_with('**/*.py', recursive=True)
            platform.system.assert_called_once_with()
            if expectedMapParallel:
               Process.run_parallel_processpoolexecutor.assert_called_once_with(Python.run_pylint_on_file, PyFilePaths)
               Process.run_parallel_processthread.assert_not_called()
            else:
               Process.run_parallel_processpoolexecutor.assert_not_called()
               Process.run_parallel_processthread.assert_called_once_with(PythonTests.ExpectedPylintCommand, PyFilePaths)
            if expectSysExit1:
               sys.exit.assert_called_once_with(1)
            else:
               sys.exit.assert_not_called()
      testcase('Linux', True, True, False)
      testcase('Windows', False, False, True)
      testcase('windows', True, False, True)

   def run_all_with_coverage_RunsCoverage_RunsReport_RunsHtml_RunsXml_ExitsWithReportExitCode_test(self):
      @patch('os.getcwd', spec_set=True)
      @patch('CloudundancyPyUtils.Process.fail_fast_run', spec_set=True)
      @patch('CloudundancyPyUtils.Process.run_and_get_exit_code', spec_set=True)
      @patch('sys.exit', spec_set=True)
      @patch('builtins.print', spec_set=True)
      def testcase(reportExitCode, expectedConcludingPrint, printMock, _2, _3, _4, _5):
         currentWorkingDirectory = Random.string()
         os.getcwd.return_value = currentWorkingDirectory
         Process.run_and_get_exit_code.return_value = reportExitCode
         testsProjectName = Random.string()
         omitPattern = Random.string()
         #
         Python.run_all_tests_with_coverage(testsProjectName, omitPattern)
         #
         self.assertEqual(2, len(printMock.call_args_list))
         printMock.assert_has_calls([call(f'Running {testsProjectName}/RunAll.py with coverage from', currentWorkingDirectory)])
         Process.run_and_get_exit_code.assert_called_once_with(f'coverage report --omit="{omitPattern}" --fail-under=100 --show-missing')
         self.assertEqual(3, len(Process.fail_fast_run.call_args_list))
         Process.fail_fast_run.assert_has_calls([
            call(f'coverage run --branch {testsProjectName}/RunAll.py'),
            call(f'coverage xml --omit="{omitPattern}" -o {testsProjectName}/CoberturaCodeCoverageResults_{testsProjectName}.xml'),
            call(f'coverage html --omit="{omitPattern}" --directory={testsProjectName}/CodeCoverageHTMLReport --title="{testsProjectName} Code Coverage"')])
         printMock.assert_has_calls([call(expectedConcludingPrint)])
         sys.exit.assert_called_once_with(reportExitCode)
      expectedFailureMessage = 'Failure. Code coverage is less than 100%.'
      testcase(-1, expectedFailureMessage)
      testcase(0, 'Success. Code coverage is 100%.')
      testcase(1, expectedFailureMessage)
      testcase(2, expectedFailureMessage)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(PythonTests, testNames)
