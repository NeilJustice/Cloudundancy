import glob
import os
import multiprocessing
import platform
import sys
from CloudundancyDevOpsPython import Process

PylintCommand = 'pylint --rcfile=.pylintrc --score=n '

def run_flake8() -> None:
   cpuCount = multiprocessing.cpu_count()
   flake8Command = f'flake8 -j {cpuCount} --config=.flake8 --show-source --benchmark'
   Process.fail_fast_run(flake8Command)

def run_mypy() -> None:
   Process.fail_fast_run('mypy .')

def run_pylint_on_file(pythonFilePath: str) -> int:
   pylintCommand = PylintCommand + pythonFilePath
   pylintExitCode = Process.run_and_get_exit_code(pylintCommand)
   return pylintExitCode

def run_pylint_on_all_files_in_parallel() -> None:
   pyFilePaths = glob.glob('**/*.py', recursive=True)
   allPylintProcessesSucceeded = False
   if platform.system() == 'Windows':
      allPylintProcessesSucceeded = Process.run_parallel_processthread(PylintCommand, pyFilePaths)
   else:
      allPylintProcessesSucceeded = Process.run_parallel_processpoolexecutor(run_pylint_on_file, pyFilePaths)
   if not allPylintProcessesSucceeded:
      sys.exit(1)

def run_all_tests_with_coverage(testsProjectName: str, omitPattern: str) -> None:
   print(f'Running {testsProjectName}/RunAll.py with coverage from', os.getcwd())
   Process.fail_fast_run(f'coverage run --branch {testsProjectName}/RunAll.py')
   reportExitCode = Process.run_and_get_exit_code(f'coverage report --omit="{omitPattern}" --fail-under=100 --show-missing')
   Process.fail_fast_run(f'coverage xml --omit="{omitPattern}" -o {testsProjectName}/CoberturaCodeCoverageResults_{testsProjectName}.xml')
   Process.fail_fast_run(f'coverage html --omit="{omitPattern}" --directory={testsProjectName}/CodeCoverageHTMLReport --title="{testsProjectName} Code Coverage"')
   if reportExitCode == 0:
      print('Success. Code coverage is 100%.')
   else:
      print('Failure. Code coverage is less than 100%.')
   sys.exit(reportExitCode)
