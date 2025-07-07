#!/bin/bash
set -ev

export PYTHONPATH=CloudundancyDevOpsPython
export CXX=clang++
python -u CloudundancyDevOpsPython/CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=Debug \
   --tests-project=libCloudundancyTests \
   --cmake-definitions="-DClangCodeCoverageMode=ON" \
   --no-install

LinuxCodeCoverageRunner measure-cplusplus-code-coverage --solution=Cloudundancy --tests-project=libCloudundancyTests
