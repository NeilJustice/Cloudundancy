#!/bin/bash
set -eu
CXX=clang++ cmake -H. -BDebug -GNinja -DCMAKE_BUILD_TYPE=Debug -DClangTidyMode=ON
(cd Debug; ninja clang-tidy)
