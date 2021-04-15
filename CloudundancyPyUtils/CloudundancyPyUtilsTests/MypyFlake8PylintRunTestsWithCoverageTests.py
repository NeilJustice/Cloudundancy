import unittest
from unittest.mock import patch
import docopt
from CloudundancyPyUtils import MypyFlake8PylintRunTestsWithCoverage, Python, Process # pylint:disable=no-name-in-module
from CloudundancyPyUtilsTests import UnitTester, Random

testNames = [
'docstring_ReturnsExpected_test',
'main_RunTestsWithCoverage_Pylints_Flake8s_CopiesSpecifiedFolderToInstallFolder_test'
]

class MypyFlake8PylintRunTestsWithCoverageTests(unittest.TestCase):

   def docstring_ReturnsExpected_test(self):
      self.assertEqual("""MypyFlake8PylintRunTestsWithCoverage.py - Runs Mypy, flake8, pylint, then runs all unit tests with code coverage.

Usage: MypyFlake8PylintRunTestsWithCoverage.py --project=<FolderName> --run-tests-with-coverage-python-file=<RelativeFilePath>""",
MypyFlake8PylintRunTestsWithCoverage.__doc__)

   @patch('docopt.docopt', spec_set=True)
   @patch('CloudundancyPyUtils.Process.fail_fast_run', spec_set=True)
   @patch('CloudundancyPyUtils.Python.flake8_all', spec_set=True)
   @patch('CloudundancyPyUtils.Python.pylint_all', spec_set=True)
   def main_RunTestsWithCoverage_Pylints_Flake8s_CopiesSpecifiedFolderToInstallFolder_test(self, _1, _2, _3, _4):
      projectFolderName = Random.string()
      runTestsWithCoveragePythonFileName = Random.string()
      docopt.docopt.return_value =\
      {
         '--project': projectFolderName,
         '--run-tests-with-coverage-python-file': runTestsWithCoveragePythonFileName
      }
      #
      MypyFlake8PylintRunTestsWithCoverage.main()
      #
      docopt.docopt.assert_called_once_with(MypyFlake8PylintRunTestsWithCoverage.__doc__)
      expectedRunTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
      Python.flake8_all.assert_called_once_with()
      Python.pylint_all.assert_called_once_with()
      Process.fail_fast_run.assert_called_once_with(expectedRunTestsWithCoverageCommand)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(MypyFlake8PylintRunTestsWithCoverageTests, testNames)
