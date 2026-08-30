#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=Cloudundancy \
   --configuration=Debug \
   --cmake-definitions="" \
   --install=false
