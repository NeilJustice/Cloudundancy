#!/bin/bash
set -v

cores=$(grep -c ^processor /proc/cpuinfo)
cppcheck \
   --enable=all \
   --cppcheck-build-dir=Cppcheck \
   --suppressions-list=CppcheckSuppressions.txt \
   -D__linux__ \
   -DTEST \
   -DTESTS \
   -DTHEN_RUN_TEMPLATE_TESTS \
   -DMETALMOCK_NONVOID0_STATIC \
   -DMETALMOCK_NONVOID0_FREE \
   -DMETALMOCK_NONVOID1_STATIC \
   -DMETALMOCK_NONVOID1_FREE \
   -DMETALMOCK_NONVOID1_CONST \
   -DMETALMOCK_VOID1 \
   -DMETALMOCK_VOID1_FREE \
   -DMETALMOCK_VOID2_CONST \
   -DMETALMOCK_NONVOID2_STATIC \
   -DMETALMOCK_NONVOID5_FREE \
   -I /usr/include/c++/v1 \
   -I /usr/local/include/ZenUnitAndMetalMock \
   -I libCloudundancy \
   -I . \
   -j "$cores" \
   --output-file=cppcheck_results.txt \
   --error-exitcode=1 \
   .
if [ $? = 1 ]; then
   echo "Cppcheck failed with exit code 1"
   exit 1
fi

