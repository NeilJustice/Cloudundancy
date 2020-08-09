"""CoverageLintInstallPythonLibrary.py
Runs coverage, pylint, flake8, then copies a folder to an install folder.

Usage: CoverageLintInstallPythonLibrary.py --project=<FolderName> --test-project=<FolderName> --run-tests-with-coverage-python-file=<FileName>"""
import os
import sys
sys.path.append('.') # Jenkins
import docopt
from PyUtils import Python, Process

def main():
   arguments = docopt.docopt(__doc__)
   testProjectFolderName = arguments['--test-project']
   runTestsWithCoveragePythonFileName = arguments['--run-tests-with-coverage-python-file']
   os.chdir(testProjectFolderName)
   runTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
   Process.fail_fast_run(runTestsWithCoverageCommand)
   os.chdir('..')
   Python.flake8_all()
   Python.pylint_all()

if __name__ == '__main__': # pragma nocover
   main()
