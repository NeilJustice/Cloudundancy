#pragma once

struct CloudundancyArgs
{
   static const std::string CommandLineUsage;

   ProgramMode programMode = ProgramMode::Unset;
   fs::path iniInputFilePath;
   bool deleteDestinationFoldersFirst = false;
   fs::path sevenZipModeIniInputFilePath;
   fs::path sevenZipStagingFolderPath;
   fs::path sevenZipFileCopyingIniInputFilePath;
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
