import sys
sys.path.append('.')
from CloudundancyPyUtils import Python

Python.run_all_tests_with_coverage(testsProjectName='CloudundancyPyUtilsTests', omitPattern='/usr/*,/home/*/.local/lib/python3.9/site-packages/*')