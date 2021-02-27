#!/bin/bash
set -eu

export PYTHONPATH=CloudundancyPyUtils
export CXX=clang++
python -u CloudundancyPyUtils/CloudundancyPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangAddressSanitizerMode=ON" \
   --no-install
