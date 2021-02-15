#!/bin/bash
set -euv

cd CloudundancyPyUtils
export PYTHONPATH=.
python CloudundancyPyUtils/CoverageLintInstallPythonLibrary.py \
	--project=CloudundancyPyUtils \
	--run-tests-with-coverage-python-file=CloudundancyPyUtilsTests/RunAllWithCoverage.py
cd ..

