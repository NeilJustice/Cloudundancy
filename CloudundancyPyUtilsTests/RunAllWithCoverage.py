import sys
sys.path.append('.')
from CloudundancyPyUtils import Python

Python.run_all_with_coverage(testsProjectName='CloudundancyPyUtilsTests', omitPattern='/usr/*')