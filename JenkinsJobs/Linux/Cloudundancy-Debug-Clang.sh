#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=clang++
python -u CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=Debug \
   --tests-project=libCloudundancyTests \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON" \
   --no-install
