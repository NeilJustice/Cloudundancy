#!/bin/bash
set -v

cppcheck \
   --enable=all \
   --cppcheck-build-dir=Cppcheck \
   --suppressions-list=CppcheckSuppressions.txt \
   -D__linux__ \
   -DTEST \
   -DTHEN_RUN_TEMPLATE_TESTS \
   -I /usr/include/c++/v1 \
   -I /usr/local/include/ZenUnitAndMetalMock \
   -I libCloudundancy \
   -I . \
   -j 64 \
   --output-file=cppcheck_results.txt \
   --error-exitcode=1 \
   .
if [ $? = 1 ]; then
   echo "Cppcheck failed with exit code 1"
   exit 1
fi
