#pragma once

struct CloudundancyIni
{
   vector<fs::path> destinationFolderPaths;
   vector<AbsoluteFileOrFolderPathToRelativeFolderPath> absoluteFileOrFolderPathAndRelativeFolderPaths;
   vector<string> fileSubpathsToNotCopy;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(CloudundancyIni) == 96);
   #else
      static_assert(sizeof(CloudundancyIni) == 72);
   #endif
#endif
