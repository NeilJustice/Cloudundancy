#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=g++
python -u CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=Release \
   --tests-project=libCloudundancyTests \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON" \
   --no-install
