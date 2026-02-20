#include "pch.h"
#include "libCloudundancy/Components/Args/CopyFilesToMultipleFoldersArgsParser.h"
#include "libCloudundancy/Components/Args/ExampleLinuxIniFileArgsParser.h"
#include "libCloudundancy/Components/Args/ExampleWindowsIniFileArgsParser.h"
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParserFactory.h"
#include "libCloudundancy/Components/Args/SevenZipArgsParser.h"

shared_ptr<const ProgramModeSpecificArgsParser> ProgramModeSpecificArgsParserFactory::NewProgramModeSpecificArgsParser(
   ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::ExampleLinuxIniFile: return make_shared<ExampleLinuxIniFileArgsParser>();
   case ProgramMode::ExampleWindowsIniFile: return make_shared<ExampleWindowsIniFileArgsParser>();
   case ProgramMode::CopyFilesToMultipleFolders: return make_shared<CopyFilesToMultipleFoldersArgsParser>();
   case ProgramMode::SevenZip: return make_shared<SevenZipArgsParser>();
   default:
   {
      const string exceptionMessage = Utils::String::ConcatValues(
         "ProgramModeSpecificArgsParserFactory::NewProgramModeSpecificArgsParser called with invalid programMode ", programMode);
      throw invalid_argument(exceptionMessage);
   }
   }
}
