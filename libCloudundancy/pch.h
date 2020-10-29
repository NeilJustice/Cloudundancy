#pragma once
#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"
#include "libCloudundancy/CompilerWarnings/IfWindowsPushIgnoredPrecompiledHeaderWarnings.h"

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
#ifdef __linux__
#include <memory>
#endif
#include <regex>
#include <sstream>
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
#endif

// libCloudundancy Enums
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"
#include "libCloudundancy/Enums/WindowsColor.h"

#include "libCloudundancy/CompilerWarnings/IfWindowsPopIgnoredPrecompiledHeaderWarnings.h"

// libCloudundancy Utilities
#include "libCloudundancy/Utilities/ReleaseAssert.h"
#include "libCloudundancy/Utilities/StringUtil.h"
