import os
import sys
print(os.getcwd())
print(sys.path)
sys.path.append('.')
from PyUtils import Python

Python.run_all_with_coverage('/usr/*')
