#!/bin/bash
set -eu
export CXX=clang++
python3 -u PyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --cmake-build-type=Release \
   --tests-project-name=libCloudundancyTests \
   --install
