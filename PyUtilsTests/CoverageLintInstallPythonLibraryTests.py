import os
import unittest
from unittest.mock import patch
from unittest.mock import call
import docopt
from PyUtils import CoverageLintInstallPythonLibrary, Python, Process, UnitTester, Random

testNames = [
'docstring_ReturnsExpected_test',
'main_RunTestsWithCoverage_Pylints_Flake8s_CopiesSpecifiedFolderToInstallFolder_test'
]

class CoverageLintInstallPythonLibraryTests(unittest.TestCase):

   def docstring_ReturnsExpected_test(self):
      self.assertEqual("""CoverageLintInstallPythonLibrary.py
Runs coverage, pylint, flake8, then copies a folder to an install folder.

Usage: CoverageLintInstallPythonLibrary.py --project=<FolderName> --test-project=<FolderName> --run-tests-with-coverage-python-file=<FileName>""",
CoverageLintInstallPythonLibrary.__doc__)

   @patch('docopt.docopt', spec_set=True)
   @patch('os.chdir', spec_set=True)
   @patch('PyUtils.Process.fail_fast_run', spec_set=True)
   @patch('PyUtils.Python.flake8_all', spec_set=True)
   @patch('PyUtils.Python.pylint_all', spec_set=True)
   def main_RunTestsWithCoverage_Pylints_Flake8s_CopiesSpecifiedFolderToInstallFolder_test(
      self, _1, _2, _3, _4, _5):
      projectFolderName = Random.string()
      testProjectFolderName = Random.string()
      runTestsWithCoveragePythonFileName = Random.string()
      docopt.docopt.return_value =\
      {
         '--project': projectFolderName,
         '--test-project': testProjectFolderName,
         '--run-tests-with-coverage-python-file': runTestsWithCoveragePythonFileName
      }
      #
      CoverageLintInstallPythonLibrary.main()
      #
      docopt.docopt.assert_called_once_with(CoverageLintInstallPythonLibrary.__doc__)
      self.assertEqual(2, len(os.chdir.call_args_list))
      os.chdir.assert_has_calls([
         call(testProjectFolderName),
         call('..')])
      expectedRunTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
      Process.fail_fast_run.assert_called_once_with(expectedRunTestsWithCoverageCommand)
      Python.flake8_all.assert_called_once_with()
      Python.pylint_all.assert_called_once_with()

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CoverageLintInstallPythonLibraryTests, testNames)
