#!/bin/bash
set -eu
export CXX=g++
python -u PyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --tests-project=libCloudundancyTests \
   --no-install
