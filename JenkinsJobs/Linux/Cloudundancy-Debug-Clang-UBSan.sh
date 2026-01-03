#!/bin/bash
set -ev

export PYTHONPATH=CloudundancyDevOpsPython
export CXX=clang++
python -u CloudundancyDevOpsPython/CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=Debug \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --no-install
