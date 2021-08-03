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

#include <regex>
namespace fs = std::filesystem;
using namespace std;

#include "ZenUnitAndMetalMock/ZenUnit.h"
#include "ZenUnitAndMetalMock/MetalMock.h"

// libCloudundancy Enums
#include "libCloudundancy/Enums/ENUM_STRING_ARRAY.h"
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"
#include "libCloudundancy/Enums/ProgramMode.h"
#include "libCloudundancy/Enums/WindowsColor.h"

// libCloudundancy Exceptions
#include "libCloudundancy/Exceptions/FileSystemExceptions.h"

// libCloudundancy ValueTypes
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancy/ValueTypes/ProcessResult.h"

// libCloudundancy StaticUtilities
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"
#include "libCloudundancy/StaticUtilities/Type.h"
#include "libCloudundancy/StaticUtilities/Vector.h"

// libCloudundancy UtilityComponents Mocks
#include "libCloudundancyTests/UtilityComponents/Assertion/MetalMock/AsserterMock.h"
#include "libCloudundancyTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancyTests/UtilityComponents/Console/MetalMock/ConsoleColorerMock.h"
#include "libCloudundancyTests/UtilityComponents/Docopt/MetalMock/DocoptParserMock.h"
#include "libCloudundancyTests/UtilityComponents/Environment/MetalMock/EnvironmentServiceMock.h"
#include "libCloudundancyTests/UtilityComponents/Exception/MetalMock/TryCatchCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/RecursiveDirectoryIteratorMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/Iteration/ForEach/MetalMock/MemberFunctionForEacherMock.h"
#include "libCloudundancyTests/UtilityComponents/Iteration/ForEach/MetalMock/OneExtraArgMemberFunctionForEacherMock.h"
#include "libCloudundancyTests/UtilityComponents/Iteration/Transform/MetalMock/OneExtraArgTransformerMock.h"
#include "libCloudundancyTests/UtilityComponents/Process/MetalMock/ProcessRunnerMock.h"
#include "libCloudundancyTests/UtilityComponents/Random/MetalMock/UtilsRandomGeneratorMock.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/WatchMock.h"

// libCloudundancyTests ValueTypes ZenUnit Equalizers And Randoms
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
