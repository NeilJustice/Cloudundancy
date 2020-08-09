#pragma once
#include "libCloudundancy/Components/Compiler/MSVCIgnoredWallWarnings.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4242) // conversion from 'int' to 'char', possible loss of data
#pragma warning(disable: 4244) // '=': conversion from 'int' to 'char', possible loss of data
#pragma warning(disable: 4365) // signed / unsigned mismatch
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif

#include <algorithm>
#include <array>
#include <assert.h>

#if defined __linux__
   #include <experimental/filesystem>
   namespace fs = std::experimental::filesystem;
   #include <unistd.h>
#elif defined _WIN32 || defined __APPLE__
   #define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
   #include <filesystem>
   namespace fs = std::filesystem;
#endif

#include <fstream>
#include <future>
#ifdef _WIN32
#include <io.h> // _isatty()
#endif
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <regex>
#include <sstream>
#ifdef _WIN32
#pragma warning(pop)
#endif
#ifdef __linux__
#include <unordered_map>
#endif
#include <unordered_set>
using namespace std;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#include "tlhelp32.h"
#endif

#include "libCloudundancy/Enums/FileSystemExceptionType.h"
