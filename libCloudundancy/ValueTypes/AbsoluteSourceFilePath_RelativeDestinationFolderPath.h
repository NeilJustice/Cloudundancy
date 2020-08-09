#pragma once
struct AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath;

struct AbsoluteSourceFilePath_RelativeDestinationFolderPath
{
   fs::path absoluteSourceFilePath;
   fs::path relativeDestinationFolderPath;

   static AbsoluteSourceFilePath_RelativeDestinationFolderPath FromCloudundancyIniCopyInstruction(
      size_t elementIndex,
      const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& absoluteSourceFileOrFolderPath_RelativeDestinationFolderPath,
      const vector<string>& fileSubpathsToNotCopy);
};
