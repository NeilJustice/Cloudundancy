#!/bin/bash
set -eu
CXX=clang++ cmake -H. -BRelease -GNinja -DCMAKE_BUILD_TYPE=Release -DClangTidyMode=ON
(cd Release; ninja clang-tidy)
