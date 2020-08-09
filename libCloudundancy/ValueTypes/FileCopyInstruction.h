#pragma once
struct AbsoluteFileOrFolderPathToRelativeFolderPath;

struct FileCopyInstruction
{
   fs::path absoluteSourceFilePath;
   fs::path absoluteDestinationFilePath;

   static FileCopyInstruction FromCloudundancyIniCopyInstruction(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath);
};
