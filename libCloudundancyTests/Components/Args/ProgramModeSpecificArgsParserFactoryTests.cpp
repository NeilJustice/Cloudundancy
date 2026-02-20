#include "pch.h"
#include "libCloudundancy/Components/Args/CopyFilesToMultipleFoldersArgsParser.h"
#include "libCloudundancy/Components/Args/ExampleLinuxIniFileArgsParser.h"
#include "libCloudundancy/Components/Args/ExampleWindowsIniFileArgsParser.h"
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParserFactory.h"
#include "libCloudundancy/Components/Args/SevenZipArgsParser.h"

TESTS(ProgramModeSpecificArgsParserFactoryTests)
AFACT(NewProgramModeSpecificArgsParser__ExampleLinuxIniFile)
AFACT(NewProgramModeSpecificArgsParser__ExampleWindowsIniFile)
AFACT(NewProgramModeSpecificArgsParser__CopyFilesToMultipleFolders)
AFACT(NewProgramModeSpecificArgsParser__SevenZip)
FACTS(NewProgramModeSpecificArgsParser__Invalid)
EVIDENCE

ProgramModeSpecificArgsParserFactory _programModeSpecificArgsParserFactory;

TEST(NewProgramModeSpecificArgsParser__ExampleLinuxIniFile)
{
   const shared_ptr<const ProgramModeSpecificArgsParser> programModeSpecificArgsParser =
      _programModeSpecificArgsParserFactory.NewProgramModeSpecificArgsParser(ProgramMode::ExampleLinuxIniFile);
   POINTEE_IS_EXACT_TYPE(ExampleLinuxIniFileArgsParser, programModeSpecificArgsParser);
}

TEST(NewProgramModeSpecificArgsParser__ExampleWindowsIniFile)
{
   const shared_ptr<const ProgramModeSpecificArgsParser> programModeSpecificArgsParser =
      _programModeSpecificArgsParserFactory.NewProgramModeSpecificArgsParser(ProgramMode::ExampleWindowsIniFile);
   POINTEE_IS_EXACT_TYPE(ExampleWindowsIniFileArgsParser, programModeSpecificArgsParser);
}

TEST(NewProgramModeSpecificArgsParser__CopyFilesToMultipleFolders)
{
   const shared_ptr<const ProgramModeSpecificArgsParser> programModeSpecificArgsParser =
      _programModeSpecificArgsParserFactory.NewProgramModeSpecificArgsParser(ProgramMode::CopyFilesToMultipleFolders);
   POINTEE_IS_EXACT_TYPE(CopyFilesToMultipleFoldersArgsParser, programModeSpecificArgsParser);
}

TEST(NewProgramModeSpecificArgsParser__SevenZip)
{
   const shared_ptr<const ProgramModeSpecificArgsParser> programModeSpecificArgsParser =
      _programModeSpecificArgsParserFactory.NewProgramModeSpecificArgsParser(ProgramMode::SevenZip);
   POINTEE_IS_EXACT_TYPE(SevenZipArgsParser, programModeSpecificArgsParser);
}

TEST1X1(NewProgramModeSpecificArgsParser__Invalid,
   ProgramMode invalidProgramMode,
   ProgramMode::Unset,
   ProgramMode::Invalid,
   ProgramMode::MaxValue)
{
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "ProgramModeSpecificArgsParserFactory::NewProgramModeSpecificArgsParser called with invalid programMode ", invalidProgramMode);
   THROWS_EXCEPTION(_programModeSpecificArgsParserFactory.NewProgramModeSpecificArgsParser(invalidProgramMode),
      invalid_argument, expectedExceptionMessage);
}

RUN_TESTS(ProgramModeSpecificArgsParserFactoryTests)
