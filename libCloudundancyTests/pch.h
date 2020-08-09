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
#include "MetalMock.h"

#include "libCloudundancy/Components/DataStructure/Vector.h"
#include "libCloudundancy/Components/Exception/Exception.h"
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"
#include "libCloudundancy/Components/FileSystem/FileSystemException.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"

#include "libCloudundancyTests/Components/Assertion/MetalMock/AsserterMock.h"
#include "libCloudundancyTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancyTests/Components/Docopt/MetalMock/DocoptParserMock.h"
#include "libCloudundancyTests/Components/Docopt/ZenUnit/docoptvalueRandom.h"
#include "libCloudundancyTests/Components/Exception/MetalMock/TryCatchCallerMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libCloudundancyTests/Components/Function/Member/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Function/Member/MetalMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Iteration/ForEach/MetalMock/OneExtraArgMemberForEacherMock.h"
#include "libCloudundancyTests/Components/Iteration/Transform/MetalMock/OneExtraArgTransformerMock.h"
#include "libCloudundancyTests/Components/Process/MetalMock/ProcessRunnerMock.h"
#include "libCloudundancyTests/Components/Time/MetalMock/StopwatchMock.h"
#include "libCloudundancyTests/Components/Time/MetalMock/WatchMock.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyArgsEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyIniEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFileOrFolderPathToRelativeFolderPathEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FilePathLineNumberLineTextEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyArgs.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyIni.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFileCopyInstruction.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFilePathLineNumberLineText.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"
