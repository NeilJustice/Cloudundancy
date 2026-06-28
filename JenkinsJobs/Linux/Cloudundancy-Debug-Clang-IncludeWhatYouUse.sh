#!/usr/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-program \
   --solution-name=Cloudundancy \
   --configuration=Debug \
   --cmake-definitions="-DIncludeWhatYouUseMode=ON" \
   --install=false \
   --standard-output-file="/code/IncludeWhatYouUseReports/Cloudundancy_iwyu_report.txt"
