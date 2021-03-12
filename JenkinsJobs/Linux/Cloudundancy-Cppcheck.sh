#!/bin/bash
set -ev

cppcheck \
   --enable=all \
   -DTEST \
   -I /usr/include/c++/v1 \
   -I /usr/local/include/ZenUnitAndMetalMock \
   -I libCloudundancy \
   -I . \
   -j 64 \
   .

