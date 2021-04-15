#!/bin/bash
set -ev

cd CloudundancyPyUtils
export PYTHONPATH='.'
python CloudundancyPyUtils/MypyFlake8PylintRunTestsWithCoverage.py \
   --project=Cloudundancy \
   --run-tests-with-coverage-python-file=CloudundancyPyUtilsTests/RunAllWithCoverage.py
cd ..
