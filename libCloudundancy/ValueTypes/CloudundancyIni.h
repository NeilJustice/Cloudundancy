#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath.h"

struct CloudundancyIni
{
   vector<fs::path> destinationFolderPaths;
   vector<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath> absoluteFileOrFolderPathAndRelativeFolderPaths;
   vector<string> fileSubpathsToNotCopy;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(CloudundancyIni) == 96);
   #else
      static_assert(sizeof(CloudundancyIni) == 72);
   #endif
#endif
