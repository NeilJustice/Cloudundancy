#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=g++
python -u CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --tests-project=libCloudundancyTests \
   --no-install
