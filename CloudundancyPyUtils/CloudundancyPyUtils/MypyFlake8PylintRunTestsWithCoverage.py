"""MypyFlake8PylintRunTestsWithCoverage.py - Runs flake8, then pylint, then unit tests with code coverage.

Usage: MypyFlake8PylintRunTestsWithCoverage.py --project=<FolderName> --run-tests-with-coverage-python-file=<RelativeFilePath>"""
import docopt
from CloudundancyPyUtils import Python, Process

def main() -> None:
   arguments = docopt.docopt(__doc__)
   runTestsWithCoveragePythonFileName = arguments['--run-tests-with-coverage-python-file']
   Python.flake8_all()
   Python.pylint_all()
   runTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
   Process.fail_fast_run(runTestsWithCoverageCommand)

if __name__ == '__main__': # pragma nocover
   main()
