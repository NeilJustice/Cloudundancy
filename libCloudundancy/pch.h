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

#if defined __linux__ || defined __APPLE__
   #include <memory>
   #include <unistd.h>
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
namespace fs = std::filesystem;
using namespace std;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include <io.h> // _isatty()
#include "Windows.h" // Windows process running of 7z.exe and console colors
#endif

// libCloudundancy Enums
#include "libCloudundancy/Enums/ENUM_STRING_ARRAY.h"
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"
#include "libCloudundancy/Enums/ProgramMode.h"
#include "libCloudundancy/Enums/WindowsColor.h"

// libCloudundancy Exceptions
#include "libCloudundancy/Exceptions/FileSystemExceptions.h"

// libCloudundancy ValueTypes
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancy/ValueTypes/ProcessResult.h"

// libCloudundancy StaticUtilities
#include "libCloudundancy/StaticUtilities/Chars.h"
#include "libCloudundancy/StaticUtilities/Map.h"
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"
#include "libCloudundancy/StaticUtilities/Type.h"
#include "libCloudundancy/StaticUtilities/Vector.h"

// libCloudundancy UtilityComponents
#include "libCloudundancy/UtilityComponents/Assertion/Asserter.h"
#include "libCloudundancy/UtilityComponents/Console/Console.h"
#include "libCloudundancy/UtilityComponents/Console/ConsoleColorer.h"
#include "libCloudundancy/UtilityComponents/Docopt/docopt.h"
#include "libCloudundancy/UtilityComponents/Docopt/DocoptParser.h"
#include "libCloudundancy/UtilityComponents/Environment/EnvironmentService.h"
#include "libCloudundancy/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"
#include "libCloudundancy/UtilityComponents/Exception/TryCatchCaller.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RawFileSystem.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RecursiveDirectoryIterator.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/NonVoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/OneExtraArgMemberFunctionForEacher.h"
#include "libCloudundancy/UtilityComponents/Iteration/Transform/OneExtraArgTransformer.h"
#include "libCloudundancy/UtilityComponents/Memory/CharVectorAllocator.h"
#include "libCloudundancy/UtilityComponents/Process/ProcessRunner.h"
#include "libCloudundancy/UtilityComponents/Time/CRTWatch.h"
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"
#include "libCloudundancy/UtilityComponents/Time/Watch.h"
