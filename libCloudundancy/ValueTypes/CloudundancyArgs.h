#pragma once

struct CloudundancyArgs
{
   static const std::string CommandLineUsage;

   ProgramMode programMode = ProgramMode::Unset;
   fs::path iniFilePath;
   bool deleteDestinationFoldersFirst = false;
   fs::path sevenZipModeIniFilePath;
   fs::path sevenZipStagingFolderPath;
   fs::path sevenZipFileCopyingIniFilePath;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(CloudundancyArgs) == 176);
   #else
      static_assert(sizeof(CloudundancyArgs) == 144);
   #endif
#elifdef __linux__
   #ifdef _LIBCPP_VERSION
      static_assert(sizeof(CloudundancyArgs) == 112);
   #else
      static_assert(sizeof(CloudundancyArgs) == 176);
   #endif
#endif
