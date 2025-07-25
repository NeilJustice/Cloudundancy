#!/bin/bash
set -ev

export PYTHONPATH=CloudundancyDevOpsPython
export CXX=g++
python -u CloudundancyDevOpsPython/CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=Debug \
   --tests-project=libCloudundancyTests \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON" \
   --no-install
