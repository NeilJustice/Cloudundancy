#!/bin/bash
set -ev

cd CloudundancyDevOpsPython
export PYTHONPATH='.'
python CloudundancyDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=CloudundancyDevOpsPythonTests/RunAllWithCoverage.py
cd ..
