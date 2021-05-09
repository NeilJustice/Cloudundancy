#!/bin/bash
set -ev

export PYTHONPATH=CloudundancyDevOpsPython
export CXX=clang++
export UBSAN_OPTIONS=halt_on_error=true
python -u CloudundancyDevOpsPython/CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --no-install
