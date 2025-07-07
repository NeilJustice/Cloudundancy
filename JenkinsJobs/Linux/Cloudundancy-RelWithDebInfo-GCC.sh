#!/bin/bash
set -ev

export PYTHONPATH=CloudundancyDevOpsPython
export CXX=g++
python -u CloudundancyDevOpsPython/CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=RelWithDebInfo \
   --tests-project=libCloudundancyTests \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON" \
   --no-install
