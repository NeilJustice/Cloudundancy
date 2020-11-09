#pragma once
#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"
#include "libCloudundancy/CompilerWarnings/IfWindowsPushIgnoredPrecompiledHeaderWarnings.h"

#ifdef _WIN32
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif

#if defined __linux__
   #include <experimental/filesystem>
   namespace fs = std::experimental::filesystem;
#elif defined _WIN32 || defined __APPLE__
   #include <filesystem>
   namespace fs = std::filesystem;
#endif
#include <regex>
using namespace std;

#include "ZenUnit.h"
#include "MetalMock.h"

// libCloudundancy Enums
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"
#include "libCloudundancy/Enums/ProgramMode.h"
#include "libCloudundancy/Enums/WindowsColor.h"

// libCloudundancy Value Types
#include "libCloudundancy/ValueTypes/AbsoluteFileOrFolderPathToRelativeFolderPath.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"

// libCloudundancy Utility Functions
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"

// libCloudundancy Utility Component Mocks
#include "libCloudundancyTests/Components/Console/MetalMock/ConsoleMock.h"

// ZenUnit Equalizers
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyArgsEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyIniEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FilePathLineNumberLineTextEqualizer.h"

// ZenUnit Randoms
#include "libCloudundancyTests/Components/Docopt/ZenUnit/docoptvalueRandom.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"
#include "libCloudundancyTests/Components/Time/ZenUnit/tmZenUnitEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyArgs.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyIni.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFileCopyInstruction.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFilePathLineNumberLineText.h"

#include "libCloudundancy/CompilerWarnings/IfWindowsPopIgnoredPrecompiledHeaderWarnings.h"
