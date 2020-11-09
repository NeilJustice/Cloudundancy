#pragma once
#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"
#include "libCloudundancy/CompilerWarnings/IfWindowsPushIgnoredPrecompiledHeaderWarnings.h"

#if defined __linux__
   #include <experimental/filesystem>
   namespace fs = std::experimental::filesystem;
   #include <memory>
   #include <unistd.h>
#elif defined _WIN32 || defined __APPLE__
   #define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
   #include <filesystem>
   namespace fs = std::filesystem;
#endif

#include <array>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include <io.h> // _isatty()
#include "Windows.h" // Windows process running of 7z.exe and console colors
#endif

// libCloudundancy Enums
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"
#include "libCloudundancy/Enums/ProgramMode.h"
#include "libCloudundancy/Enums/WindowsColor.h"

#include "libCloudundancy/CompilerWarnings/IfWindowsPopIgnoredPrecompiledHeaderWarnings.h"

// libCloudundancy Utility Components
#include "libCloudundancy/Components/Console/Console.h"

// libCloudundancy Utility Functions
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"
