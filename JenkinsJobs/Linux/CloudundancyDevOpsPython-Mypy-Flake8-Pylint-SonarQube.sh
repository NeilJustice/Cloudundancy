#!/bin/bash
set -ev

export PYTHONPATH=.
python CloudundancyDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=CloudundancyDevOpsPythonTests/RunAllWithCoverage.py
