import unittest
from unittest.mock import call, patch
import docopt
from CloudundancyDevOpsPython import MypyFlake8PylintThenRunTestsWithCoverage, Process, Python
from CloudundancyDevOpsPythonTests import Random, UnitTester

testNames = [
'test_docstring_ReturnsExpected',
'test_main_RunsMypy_Flake8_Pylint_ThenRunTestsWithCoverage'
]

class MypyFlake8PylintThenRunTestsWithCoverageTests(unittest.TestCase):

   def test_docstring_ReturnsExpected(self):
      self.assertEqual("""MypyFlake8PylintThenRunTestsWithCoverage.py
Runs mypy, flake8, pylint, then runs tests with coverage.

Usage: MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=<FilePath>""",
MypyFlake8PylintThenRunTestsWithCoverage.__doc__)

   @patch('docopt.docopt', spec_set=True)
   @patch('CloudundancyDevOpsPython.Python.run_mypy', spec_set=True)
   @patch('CloudundancyDevOpsPython.Python.run_flake8', spec_set=True)
   @patch('CloudundancyDevOpsPython.Python.run_pylint_on_all_files_in_parallel', spec_set=True)
   @patch('CloudundancyDevOpsPython.Process.fail_fast_run', spec_set=True)
   @patch('builtins.print', spec_set=True)
   def test_main_RunsMypy_Flake8_Pylint_ThenRunTestsWithCoverage(self, printMock, _2, _3, _4, _5, _6):
      runTestsWithCoveragePythonFileName = Random.string()
      docopt.docopt.return_value =\
      {
         '--run-tests-with-coverage-python-file': runTestsWithCoveragePythonFileName
      }
      #
      MypyFlake8PylintThenRunTestsWithCoverage.main()
      #
      docopt.docopt.assert_called_once_with(MypyFlake8PylintThenRunTestsWithCoverage.__doc__)
      Python.run_mypy.assert_called_once_with()
      Python.run_flake8.assert_called_once_with()
      Python.run_pylint_on_all_files_in_parallel.assert_called_once_with()
      expectedRunTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
      Process.fail_fast_run.assert_called_once_with(expectedRunTestsWithCoverageCommand)
      self.assertEqual(3, len(printMock.call_args_list))
      printMock.assert_has_calls([
         call(f'[MypyFlake8PylintThenRunTestsWithCoverage.py] --run-tests-with-coverage-python-file={runTestsWithCoveragePythonFileName}'),
         call('[MypyFlake8PylintThenRunTestsWithCoverage.py] Successfully ran mypy, flake8, pylint, and unit tests with code coverage.'),
         call('[MypyFlake8PylintThenRunTestsWithCoverage.py] ExitCode: 0')])

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(MypyFlake8PylintThenRunTestsWithCoverageTests, testNames)
