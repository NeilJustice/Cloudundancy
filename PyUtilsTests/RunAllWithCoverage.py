import sys
sys.path.append('..') # Jenkins
from PyUtils import Python

Python.run_all_with_coverage(omit='/usr/*')
