"""CoverageLintInstallPythonLibrary.py
Runs flake8, then pylint, then unit tests with code coverage.

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
