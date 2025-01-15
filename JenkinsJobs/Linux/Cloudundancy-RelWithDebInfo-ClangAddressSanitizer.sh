#!/bin/bash
set -ev

export PYTHONPATH=.
export CXX=clang++
python -u CloudundancyDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=Cloudundancy \
   --cmake-build-type=RelWithDebInfo \
   --tests-project-name=libCloudundancyTests \
   --cmake-definitions="-DClangAddressSanitizerMode=ON" \
   --no-install
