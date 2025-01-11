#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=clang++
export UBSAN_OPTIONS=halt_on_error=true
python -u CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=RelWithDebInfo \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON -DFastLinuxRelWithDebInfoBuildMode=ON" \
   --no-install
