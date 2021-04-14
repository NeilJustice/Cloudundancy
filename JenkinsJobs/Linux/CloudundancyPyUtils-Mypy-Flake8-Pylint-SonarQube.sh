#!/bin/bash
set -ev

cd CloudundancyPyUtils
export PYTHONPATH='.'
python CloudundancyPyUtils/CoverageLintInstallPythonLibrary.py --project=Cloudundancy --run-tests-with-coverage-python-file=CloudundancyPyUtilsTests/RunAllWithCoverage.py
cd ..

