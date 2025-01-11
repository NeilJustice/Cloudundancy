#!/bin/bash
set -ev

export CXX=clang++
cmake -H. -BRelWithDebInfo -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DClangTidyMode=ON
(cd RelWithDebInfo; ninja clang-tidy)
