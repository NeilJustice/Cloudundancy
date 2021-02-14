#!/bin/bash
set -eu
export PYTHONPATH=CloudundancyPyUtils
export CXX=g++
python -u CloudundancyPyUtils/CloudundancyPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --tests-project=libCloudundancyTests \
   --no-install
