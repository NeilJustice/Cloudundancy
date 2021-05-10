#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=clang++
python -u CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --tests-project=libCloudundancyTests \
   --no-install
