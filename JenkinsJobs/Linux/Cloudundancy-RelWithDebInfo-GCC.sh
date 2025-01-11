#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=g++
python -u CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=RelWithDebInfo \
   --tests-project=libCloudundancyTests \
   --cmake-definitions="-DFastLinuxRelWithDebInfoBuildMode=ON" \
   --no-install
