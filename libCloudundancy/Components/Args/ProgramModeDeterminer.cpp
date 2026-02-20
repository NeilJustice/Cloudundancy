#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"

ProgramModeDeterminer::ProgramModeDeterminer()
   // Constant Components
   : _docoptParser(make_unique<DocoptParser>())
{
}

ProgramModeDeterminer::~ProgramModeDeterminer()
{
}

ProgramMode ProgramModeDeterminer::DetermineProgramMode(const map<string, docopt::value>& docoptArgs) const
{
   const bool isExampleLinuxIniFileMode = _docoptParser->GetRequiredBool(docoptArgs, "example-linux-ini-file");
   if (isExampleLinuxIniFileMode)
   {
      return ProgramMode::ExampleLinuxIniFile;
   }

   const bool isExampleWindowsIniFileMode = _docoptParser->GetRequiredBool(docoptArgs, "example-windows-ini-file");
   if (isExampleWindowsIniFileMode)
   {
      return ProgramMode::ExampleWindowsIniFile;
   }

   const bool isCopyFileToFilesToMultipleFoldersMode = _docoptParser->GetRequiredBool(docoptArgs, "copy-files-to-multiple-folders");
   if (isCopyFileToFilesToMultipleFoldersMode)
   {
      return ProgramMode::CopyFilesToMultipleFolders;
   }

   const bool is7ZipMode = _docoptParser->GetRequiredBool(docoptArgs, "7zip-files-then-copy-the-7zip-file-to-multiple-folders");
   if (is7ZipMode)
   {
      return ProgramMode::SevenZip;
   }
   return ProgramMode::Invalid;
}
