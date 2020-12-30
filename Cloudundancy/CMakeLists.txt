cmake_minimum_required(VERSION 3.5)
project(Cloudundancy)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

source_group("" FILES CloudundancyMain.cpp)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(Cloudundancy CloudundancyMain.cpp)

target_link_libraries(Cloudundancy libCloudundancy)
if(UNIX)
   target_link_libraries(Cloudundancy stdc++fs)
endif()

install(TARGETS Cloudundancy DESTINATION "bin")

if(UNIX AND NOT APPLE)
   if(CodeCovMode)
     target_link_libraries(Cloudundancy CodeCovLibraryInterface)
   endif()
endif()
