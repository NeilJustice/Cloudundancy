#!/bin/bash
set -eu
export CXX=clang++
export UBSAN_OPTIONS=halt_on_error=true
python3 -u PyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --cmake-build-type=Release \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangSanitizerMode_Thread=ON" \
   --no-install
