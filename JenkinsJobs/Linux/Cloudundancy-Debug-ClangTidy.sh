#!/bin/bash
set -ev

export CXX=clang++
cmake -H. -BDebug -GNinja -DCMAKE_BUILD_TYPE=Debug -DClangTidyMode=ON
(cd Debug; ninja clang-tidy)
