#!/bin/bash
set -eu
export PYTHONPATH=CloudundancyPyUtils
export CXX=clang++
export UBSAN_OPTIONS=halt_on_error=true
python -u CloudundancyPyUtils/CloudundancyPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangSanitizerMode_AddressAndUndefinedBehavior=ON" \
   --no-install
