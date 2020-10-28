#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteFileOrFolderPathToRelativeFolderPath.h"

struct CloudundancyIni
{
   vector<fs::path> destinationFolderPaths;
   vector<AbsoluteFileOrFolderPathToRelativeFolderPath> absoluteFileOrFolderPathAndRelativeFolderPaths;
   vector<string> fileSubpathsToNotCopy;
};
