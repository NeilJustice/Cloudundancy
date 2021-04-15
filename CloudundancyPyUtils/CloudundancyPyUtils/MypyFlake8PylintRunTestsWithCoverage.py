"""MypyFlake8PylintRunTestsWithCoverage.py
Runs mypy, flake8, pylint, then runs tests with coverage.

Usage: MypyFlake8PylintRunTestsWithCoverage.py --run-tests-with-coverage-python-file=<FilePath>"""
import docopt # type: ignore
from CloudundancyPyUtils import Process, Python

def main() -> None:
   arguments = docopt.docopt(__doc__)
   runTestsWithCoveragePythonFileName = arguments['--run-tests-with-coverage-python-file']
   print(f'[MypyFlake8PylintRunTestsWithCoverage.py] --run-tests-with-coverage-python-file={runTestsWithCoveragePythonFileName}')
   Python.run_mypy()
   Python.run_flake8()
   Python.run_pylint_on_all_files_in_parallel()
   runTestsWithCoverageCommand = f'python {runTestsWithCoveragePythonFileName}'
   Process.fail_fast_run(runTestsWithCoverageCommand)
   print('[MypyFlake8PylintRunTestsWithCoverage.py] Successfully ran mypy, flake8, pylint, and unit tests with code coverage.')
   print('[MypyFlake8PylintRunTestsWithCoverage.py] ExitCode: 0')

if __name__ == '__main__': # pragma nocover
   main()
