#pragma once
#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"

#ifdef _WIN32
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif

#if defined __linux__
   #include <experimental/filesystem>
   namespace fs = std::experimental::filesystem;
#elif defined _WIN32 || defined __APPLE__
   #pragma warning(push)
   #pragma warning(disable: 4365) // signed/unsigned mismatch
   #include <filesystem>
   namespace fs = std::filesystem;
   #pragma warning(pop)
#endif
#include <regex>
using namespace std;

#include "ZenUnit/ZenUnit.h"
#include "ZenUnit/MetalMock.h"

// libCloudundancy Enums
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"
#include "libCloudundancy/Enums/ProgramMode.h"
#include "libCloudundancy/Enums/WindowsColor.h"

// libCloudundancy Value Types
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancy/ValueTypes/FileSystemException.h"
#include "libCloudundancy/ValueTypes/ProcessResult.h"

// libCloudundancy Utility Functions
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"

// libCloudundancy Components Mocks
#include "libCloudundancyTests/UtilityComponents/Assertion/MetalMock/AsserterMock.h"
#include "libCloudundancyTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libCloudundancyTests/UtilityComponents/Iteration/ForEach/MetalMock/MemberFunctionForEacherMock.h"
#include "libCloudundancyTests/UtilityComponents/Iteration/ForEach/MetalMock/OneExtraArgMemberFunctionForEacherMock.h"
#include "libCloudundancyTests/Components/Random/MetalMock/UtilsRandomGeneratorMock.h"

// ZenUnit Equalizers And Randoms
#include "libCloudundancyTests/ValueTypes/ZenUnit/AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniCopyInstructionEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyArgsEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniCopyInstructionEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/docoptvalueRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FileCopyResultEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FilePathLineNumberLineTextEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/ProcessResultEqualizerAndRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/tmZenUnitEqualizerAndRandom.h"
