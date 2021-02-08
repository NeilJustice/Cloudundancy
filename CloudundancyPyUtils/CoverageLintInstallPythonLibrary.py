"""CoverageLintInstallPythonLibrary.py
Runs coverage, pylint, flake8, then copies a folder to an install folder.

Usage: CoverageLintInstallPythonLibrary.py --project=<FolderName> --run-tests-with-coverage-python-file=<RelativeFilePath>"""
import docopt
from CloudundancyPyUtils import Python, Process

def main():
   arguments = docopt.docopt(__doc__)
   runTestsWithCoveragePythonFileName = arguments['--run-tests-with-coverage-python-file']
   runTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
   Python.flake8_all()
   Python.pylint_all()
   Process.fail_fast_run(runTestsWithCoverageCommand)

if __name__ == '__main__': # pragma nocover
   main()
