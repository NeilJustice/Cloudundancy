set -eux

clang++ --version
g++ --version
cmake --version
ninja --version
python3 --version

if [ "$CODE_COV_MODE" == "ON" ];
then
  gcov --version
  lcov --version
fi

mkdir build && cd build
cmake -GNinja .. -Werror=dev -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" -DCodeCovMode="$CODE_COV_MODE"
curl https://raw.githubusercontent.com/NeilJustice/ZenUnitAndMetalMock/main/ZenUnit/ZenUnit.h --create-dirs -o "$TRAVIS_BUILD_DIR/ZenUnit.h"
curl https://raw.githubusercontent.com/NeilJustice/ZenUnitAndMetalMock/main/MetalMock/MetalMock.h --create-dirs -o "$TRAVIS_BUILD_DIR/MetalMock.h"
ninja -v
./libCloudundancyTests/libCloudundancyTests --test-runs=5 --random-test-ordering --exit-1-if-tests-skipped
