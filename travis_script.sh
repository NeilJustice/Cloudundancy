#!/bin/bash
set -euv

if [ "$TRAVIS_OS_NAME" -ne "osx" ]; then
   free --human
fi
clang++ --version
g++ --version
cmake --version
ninja --version
python3 --version

if [ "$CODE_COV_MODE" = "ON" ]; then
   export LCOV_ROOT="$HOME/lcov"
   mkdir -p "$LCOV_ROOT"
   wget https://github.com/linux-test-project/lcov/releases/download/v1.15/lcov-1.15.tar.gz --output-document="$LCOV_ROOT/lcov.tar.gz"
   tar xf "$LCOV_ROOT/lcov.tar.gz" --strip-components=1 -C $LCOV_ROOT
   export PATH="$LCOV_ROOT/bin:$PATH"
   which lcov
   lcov --version
   which gcov
   gcov --version
fi

mkdir build && cd build
cmake -GNinja .. -Werror=dev -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" -DCodeCovMode="$CODE_COV_MODE"
curl https://raw.githubusercontent.com/NeilJustice/ZenUnitAndMetalMock/main/ZenUnit/ZenUnit.h --create-dirs -o "$TRAVIS_BUILD_DIR/ZenUnit/ZenUnit.h"
curl https://raw.githubusercontent.com/NeilJustice/ZenUnitAndMetalMock/main/ZenUnit/MetalMock.h --create-dirs -o "$TRAVIS_BUILD_DIR/ZenUnit/MetalMock.h"
if [ "$TRAVIS_COMPILER" = "gcc" ]; then
   # Travis GCC runs out of memory when ninja is run with full parallelism
   ninja -v -j3
else
   ninja -v
fi
./libCloudundancyTests/libCloudundancyTests --test-runs=5 --random-test-ordering --exit-1-if-tests-skipped

if [ "$CODE_COV_MODE" == "ON" ]; then
  lcov --directory . --capture --output-file coverage.info
  lcov --list coverage.info
  bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
fi
