#pragma once
#include "libCloudundancy/Compiler/IfWindowsIgnoreTheseWarningsGlobally.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4365) // signed / unsigned mismatch
#endif
#include <filesystem>
#ifdef _WIN32
#pragma warning(pop)
#endif

#include <array>
#include <functional>
#include <iostream>
#include <unordered_map>
#if defined __linux__
   #include <memory>
   #include <unistd.h>
   #ifdef _LIBCPP_VERSION
      #include <algorithm>
      #include <sstream>
      #include <type_traits>
   #endif
#endif
namespace fs = std::filesystem;
using namespace std;

#ifdef _WIN32
   #define WIN32_LEAN_AND_MEAN
   #define NOGDI
   #define NOMINMAX
   #include <io.h> // _isatty()
   #include "Windows.h" // Windows process running of 7z.exe and console colors
#endif

// libCloudundancy ValueTypes
#include "libCloudundancy/Enums/ENUM_STRING_ARRAY.h"
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"
#include "libCloudundancy/Enums/ProgramMode.h"
#include "libCloudundancy/Enums/WindowsColor.h"
#include "libCloudundancy/Exceptions/FileSystemExceptions.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancy/ValueTypes/ProcessResult.h"
// libCloudundancy Components
#include "libCloudundancy/StaticUtilities/Chars.h"
#include "libCloudundancy/StaticUtilities/Map.h"
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"
#include "libCloudundancy/StaticUtilities/Type.h"
#include "libCloudundancy/StaticUtilities/Vector.h"
#include "libCloudundancy/Components/Asserters/Asserter.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancy/Components/Environment/EnvironmentService.h"
#include "libCloudundancy/Components/ErrorHandling/ErrorCodeTranslator.h"
#include "libCloudundancy/Components/Exception/TryCatchCaller.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/FileSystem/RecursiveDirectoryIterator.h"
#include "libCloudundancy/Components/FunctionCallers/Member/NonVoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/Iteration/ForEach/TwoArgMemberFunctionForEacher.h"
#include "libCloudundancy/Components/Memory/CharVectorAllocator.h"
#include "libCloudundancy/Components/Process/ProcessRunner.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/Time/Watch.h"
