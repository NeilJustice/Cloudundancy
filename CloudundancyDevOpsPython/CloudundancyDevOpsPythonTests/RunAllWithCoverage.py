import sys
sys.path.append('.')
from CloudundancyDevOpsPython import Python

Python.run_all_tests_with_coverage(testsProjectName='CloudundancyDevOpsPythonTests', omitPattern='/usr/*,/home/*/.local/lib/python3.9/site-packages/*')
