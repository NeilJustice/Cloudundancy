#!/bin/bash
set -ev

cd CloudundancyPyUtils
export PYTHONPATH='.'
python CloudundancyPyUtils/MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=CloudundancyPyUtilsTests/RunAllWithCoverage.py
cd ..
