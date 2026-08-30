#!/bin/bash
set -ev

export CXX=clang++
export UBSAN_OPTIONS="silence_unsigned_overflow=1"
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=Cloudundancy \
   --configuration=Debug \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --install=false
