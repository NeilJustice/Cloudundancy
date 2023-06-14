cmake_minimum_required(VERSION 3.5)
project(Cloudundancy)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

source_group("" FILES CloudundancyMain.cpp)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(Cloudundancy CloudundancyMain.cpp)
if(UNIX)
   set_target_properties(Cloudundancy PROPERTIES OUTPUT_NAME cloudundancy)
endif()

target_link_libraries(Cloudundancy libCloudundancy)
set_property(TARGET Cloudundancy PROPERTY CXX_STANDARD 20)
if(UNIX)
   target_link_libraries(Cloudundancy stdc++fs)
endif()

install(TARGETS Cloudundancy DESTINATION "bin")

if(UNIX AND NOT APPLE)
   if(LCovCodeCoverageMode)
     target_link_libraries(Cloudundancy CodeCovLibraryInterface)
   endif()
endif()
