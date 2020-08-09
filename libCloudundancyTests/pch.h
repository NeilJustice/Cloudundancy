#pragma once
#include "libCloudundancy/Components/Compiler/MSVCIgnoredWallWarnings.h"

#ifdef _WIN32
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif

#include <assert.h>
#if defined __linux__
   #include <experimental/filesystem>
   namespace fs = std::experimental::filesystem;
#elif defined _WIN32 || defined __APPLE__
   #include <filesystem>
   namespace fs = std::filesystem;
#endif
#include <map>
#include <regex>
#include <unordered_set>
using namespace std;

#ifdef _WIN32
#include <io.h> // _isatty()
#endif

#include "ZenUnit.h"
#include "ZenMock.h"

#include "libCloudundancy/Components/DataStructure/Vector.h"
#include "libCloudundancy/Components/Exception/Exception.h"
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"
#include "libCloudundancy/Components/FileSystem/FileSystemException.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"

#include "libCloudundancyTests/Components/Assertion/ZenMock/AsserterMock.h"
#include "libCloudundancyTests/Components/Console/ZenMock/ConsoleMock.h"
#include "libCloudundancyTests/Components/Docopt/ZenMock/DocoptParserMock.h"
#include "libCloudundancyTests/Components/Docopt/ZenUnit/docoptvalueRandom.h"
#include "libCloudundancyTests/Components/Exception/ZenMock/TryCatchCallerMock.h"
#include "libCloudundancyTests/Components/FileSystem/ZenMock/FileSystemMock.h"
#include "libCloudundancyTests/Components/Function/Member/ZenMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/ZenMock/VoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/ZenMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/ZenMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/ZenMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Iteration/ForEach/ZenMock/OneExtraArgMemberForEacherMock.h"
#include "libCloudundancyTests/Components/Iteration/Transform/ZenMock/OneExtraArgTransformerMock.h"
#include "libCloudundancyTests/Components/Process/ZenMock/ProcessRunnerMock.h"
#include "libCloudundancyTests/Components/Time/ZenMock/StopwatchMock.h"
#include "libCloudundancyTests/Components/Time/ZenMock/WatchMock.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyArgsEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyIniEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFileOrFolderPathToRelativeFolderPathEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FilePathLineNumberLineTextEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyArgs.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyIni.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFileCopyInstruction.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFilePathLineNumberLineText.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"
