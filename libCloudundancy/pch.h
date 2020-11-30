#pragma once
#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"

#if defined __linux__
   #include <experimental/filesystem>
   namespace fs = std::experimental::filesystem;
   #include <memory>
   #include <unistd.h>
#elif defined _WIN32 || defined __APPLE__
   #pragma warning(push)
   #pragma warning(disable: 4365) // signed/unsigned mismatch
   #define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
   #include <filesystem>
   namespace fs = std::filesystem;
   #pragma warning(pop)
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

// libCloudundancy ValueTypes
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancy/ValueTypes/FileSystemException.h"
#include "libCloudundancy/ValueTypes/ProcessResult.h"

// libCloudundancy Utility Components
#include "libCloudundancy/Components/Console/Console.h"

// libCloudundancy Utility Functions
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"
