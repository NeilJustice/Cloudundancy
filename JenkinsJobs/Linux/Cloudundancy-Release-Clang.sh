#!/bin/bash
set -eu
export CXX=clang++
python -u CloudundancyPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --tests-project-name=libCloudundancyTests \
   --install
