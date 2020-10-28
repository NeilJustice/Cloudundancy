#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath.h"

struct CloudundancyIni
{
   vector<fs::path> destinationFolderPaths;
   vector<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath> absoluteFileOrFolderPathAndRelativeFolderPaths;
   vector<string> fileSubpathsToNotCopy;
};
