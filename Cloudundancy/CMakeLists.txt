cmake_minimum_required(VERSION 3.10)
project(Cloudundancy)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

source_group("" FILES CloudundancyMain.cpp)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(Cloudundancy CloudundancyMain.cpp)
if(UNIX)
   set_target_properties(Cloudundancy PROPERTIES OUTPUT_NAME cloudundancy)
endif()

target_link_libraries(Cloudundancy libCloudundancy)
if(MSVC)
   replace(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Ob1" "/Ob2")
   append(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Oi /Ot /GS- /arch:AVX2 /fp:fast")
   replace(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug" "/DEBUG:FASTLINK")
   replace(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/debug" "/DEBUG:FASTLINK")
endif()

install(TARGETS Cloudundancy DESTINATION "bin")

if(UNIX)
   if(LCovCodeCoverageMode)
     target_link_libraries(Cloudundancy CodeCovLibraryInterface)
   endif()
endif()
