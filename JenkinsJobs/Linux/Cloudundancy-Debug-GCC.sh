#!/bin/bash
set -eu
export CXX=g++
python3 -u PyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --cmake-build-type=Debug \
   --tests-project=libCloudundancyTests \
   --no-install
