#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=Cloudundancy \
   --configuration=RelWithDebInfo \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON" \
   --install=true
