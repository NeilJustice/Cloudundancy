#!/bin/bash
set -ev

export PYTHONPATH=CloudundancyDevOpsPython
export CXX=clang++
export UBSAN_OPTIONS="silence_unsigned_overflow=1"
python -u CloudundancyDevOpsPython/CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=Debug \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --no-install
