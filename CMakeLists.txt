cmake_minimum_required(VERSION 3.10)
project(Cloudundancy)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

if(UNIX)
   if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      set(CMAKE_CXX_FLAGS "-std=c++2b -stdlib=libstdc++ \
         -Weverything -Werror \
         -Wno-alloca \
         -Wno-c++98-compat \
         -Wno-c++98-compat-pedantic \
         -Wno-covered-switch-default \
         -Wno-deprecated-copy-with-dtor \
         -Wno-disabled-macro-expansion \
         -Wno-exit-time-destructors \
         -Wno-extra-semi-stmt \
         -Wno-global-constructors \
         -Wno-missing-variable-declarations \
         -Wno-padded \
         -Wno-reserved-identifier \
         -Wno-shadow-field-in-constructor \
         -Wno-switch-enum \
         -Wno-unsafe-buffer-usage \
         -Wno-weak-vtables")
      if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 21.0.0)
         append(CMAKE_CXX_FLAGS "-Wno-nrvo")
      endif ()
   elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_CXX_FLAGS "-std=c++2b -Wall -Wextra -pedantic -Werror")
   endif()
   if(FastLinuxDebugBuildMode)
      replace(CMAKE_CXX_FLAGS_DEBUG "-g" "")
      message("FastLinuxDebugBuildMode enabled: -g removed")
   endif()
   if(FastLinuxReleaseBuildMode)
      replace(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2" "")
      message("FastLinuxReleaseBuildMode enabled: -O2 removed")
   endif()
   if(ClangTidyMode)
      set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
      message("ClangTidyMode enabled: CMAKE_EXPORT_COMPILE_COMMANDS set to ON")
   elseif(ClangUndefinedBehaviorSanitizerMode)
      replace(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g" "")
      replace(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2" "")
      append(CMAKE_CXX_FLAGS "-fsanitize=undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds")
      message("ClangUndefinedBehaviorSanitizerMode enabled: -fsanitize=undefined appended to CMAKE_CXX_FLAGS")
   elseif(ClangAddressSanitizerMode)
      append(CMAKE_CXX_FLAGS "-fsanitize=address")
      message("ClangAddressSanitizerMode enabled: -fsanitize=address appended to CMAKE_CXX_FLAGS")
   elseif(ClangCodeCoverageMode)
      append(CMAKE_CXX_FLAGS "-fcoverage-mapping -fprofile-instr-generate=coverage.profraw")
      message("ClangCodeCoverageMode enabled: -fcoverage-mapping -fprofile-instr-generate=coverage.profraw appended to CMAKE_CXX_FLAGS")
   elseif(LCovCodeCoverageMode)
      replace(CMAKE_CXX_FLAGS_RELEASE "-O3" "")
      message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
      add_library(CodeCovLibraryInterface INTERFACE)
      target_compile_options(CodeCovLibraryInterface INTERFACE -O0 -g --coverage)
      target_link_libraries(CodeCovLibraryInterface INTERFACE --coverage)
   elseif(IncludeWhatYouUseMode)
      replace(CMAKE_CXX_FLAGS_DEBUG "-g" "")
      set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "/usr/bin/include-what-you-use"
         "-Xiwyu" "--keep=*pch.h"
         "-Xiwyu" "--cxx17ns"
         "-Xiwyu" "--error_always=0")
      message("IncludeWhatYouUseMode enabled: CMAKE_CXX_INCLUDE_WHAT_YOU_USE set to /usr/bin/include-what-you-use with precompiled headers and unity builds disabled")
   endif()
elseif(MSVC)
   set_property(GLOBAL PROPERTY USE_FOLDERS ON)
   set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc /Wall /WX /permissive- /MP /bigobj")
endif()

add_subdirectory(Cloudundancy)
add_subdirectory(libCloudundancy)
add_subdirectory(libCloudundancyTests)

set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo")

if(UNIX)
   include(ProcessorCount)
   ProcessorCount(NumberOfCores)
   add_custom_target(clang-tidy COMMAND
      find -name "*.cpp" -not -path "*/CMakeFiles/*" -print0 | xargs -0 -n 1 -P ${NumberOfCores} -t clang-tidy -p ${CMAKE_BUILD_TYPE}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} VERBATIM USES_TERMINAL)
endif()
