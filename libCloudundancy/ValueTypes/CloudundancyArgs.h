#pragma once
#include "libCloudundancy/Enums/ProgramMode.h"

struct CloudundancyArgs
{
   static const std::string CommandLineUsage;

   ProgramMode programMode = ProgramMode::Unset;
   fs::path iniFilePath;
   fs::path sevenZipIniFilePath;
   fs::path backupStagingFolderPath;
};
