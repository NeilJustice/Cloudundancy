#pragma once
struct AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath;

struct AbsoluteFilePathToRelativeFolderPath
{
   fs::path absoluteSourceFilePath;
   fs::path relativeDestinationFolderPath;

   static AbsoluteFilePathToRelativeFolderPath FromCloudundancyIniCopyInstruction(
      size_t elementIndex,
      const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& cloudundancyIniCopyInstruction,
      const vector<string>& fileSubpathsToNotCopy);
};
