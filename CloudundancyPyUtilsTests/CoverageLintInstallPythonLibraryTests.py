import unittest
from unittest.mock import patch
import docopt
from CloudundancyPyUtils import CoverageLintInstallPythonLibrary, Python, Process, UnitTester, Random # pylint:disable=no-name-in-module

testNames = [
'docstring_ReturnsExpected_test',
'main_RunTestsWithCoverage_Pylints_Flake8s_CopiesSpecifiedFolderToInstallFolder_test'
]

class CoverageLintInstallPythonLibraryTests(unittest.TestCase):

   def docstring_ReturnsExpected_test(self):
      self.assertEqual("""CoverageLintInstallPythonLibrary.py
Runs flake8, then pylint, then unit tests with code coverage.

Usage: CoverageLintInstallPythonLibrary.py --project=<FolderName> --run-tests-with-coverage-python-file=<RelativeFilePath>""",
CoverageLintInstallPythonLibrary.__doc__)

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
      CoverageLintInstallPythonLibrary.main()
      #
      docopt.docopt.assert_called_once_with(CoverageLintInstallPythonLibrary.__doc__)
      expectedRunTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
      Python.flake8_all.assert_called_once_with()
      Python.pylint_all.assert_called_once_with()
      Process.fail_fast_run.assert_called_once_with(expectedRunTestsWithCoverageCommand)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CoverageLintInstallPythonLibraryTests, testNames)
