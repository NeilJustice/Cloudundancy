#pragma once

struct CloudundancyArgs
{
   static const std::string CommandLineUsage;

   ProgramMode programMode = ProgramMode::Unset;
   fs::path iniFilePath;
   fs::path sevenZipIniFilePath;
   fs::path backupStagingFolderPath;
   bool deleteDestinationFoldersFirst = false;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(CloudundancyArgs) == 136);
   #else
      static_assert(sizeof(CloudundancyArgs) == 112);
   #endif
#endif
