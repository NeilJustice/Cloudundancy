#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution=Cloudundancy \
   --configuration=RelWithDebInfo \
   --cmake-definitions="-DClangAddressSanitizerMode=ON" \
   --install=false
