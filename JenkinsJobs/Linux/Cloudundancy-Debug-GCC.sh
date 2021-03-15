#!/bin/bash
set -ev

export PYTHONPATH=CloudundancyPyUtils
export CXX=g++
python -u CloudundancyPyUtils/CloudundancyPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --tests-project=libCloudundancyTests \
   --no-install
