import glob
import os
import platform
import sys
from CloudundancyPyUtils import Process

PylintCommand = 'pylint --rcfile=.pylintrc --score=n --init-hook=\"sys.path.append(\'.\')\" '

def pylint_file(pythonFilePath):
   pylintCommand = PylintCommand + pythonFilePath
   pylintExitCode = Process.run_and_get_exit_code(pylintCommand)
   return pylintExitCode

def pylint_all():
   pyFilePaths = glob.glob('**/*.py', recursive=True)
   allPylintsSucceeded = False
   if platform.system() == 'Windows':
      allPylintsSucceeded = Process.run_foreach(PylintCommand, pyFilePaths)
   else:
      allPylintsSucceeded = Process.run_parallel_ProcessPoolExecutor(pylint_file, pyFilePaths)
   if not allPylintsSucceeded:
      sys.exit(1)

def flake8_all():
   flake8Command = 'flake8 --config=.flake8 --show-source --benchmark'
   Process.fail_fast_run(flake8Command)

def run_all_with_coverage(omit):
   print('Running CloudundancyPyUtilsTests/RunAll.py with coverage from', os.getcwd())
   Process.fail_fast_run('coverage run --branch CloudundancyPyUtilsTests/RunAll.py')
   reportExitCode = Process.run_and_get_exit_code(f'coverage report --omit="{omit}" --fail-under=100 --show-missing')
   Process.fail_fast_run('coverage html')
   Process.fail_fast_run(f'coverage xml --omit="{omit}"')
   if reportExitCode == 0:
      print('Success. Coverage is 100%.')
   else:
      print('Failure. Coverage is less than 100%.')
   sys.exit(reportExitCode)