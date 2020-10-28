#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeFolderPath.h"

AbsoluteFilePathToRelativeFolderPath AbsoluteFilePathToRelativeFolderPath::FromCloudundancyIniCopyInstruction(
   size_t elementIndex,
   const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& absoluteFileOrFolderPathToRelativeFolderPath,
   const vector<string>& fileSubpathsToNotCopy)
{
   return AbsoluteFilePathToRelativeFolderPath();
}
