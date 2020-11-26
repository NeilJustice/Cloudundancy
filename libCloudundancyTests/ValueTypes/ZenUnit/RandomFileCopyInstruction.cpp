#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/RandomFileCopyInstruction.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"

namespace ZenUnit
{
   template<>
   AbsoluteFileOrFolderPathToRelativeFolderPath Random<AbsoluteFileOrFolderPathToRelativeFolderPath>()
   {
      AbsoluteFileOrFolderPathToRelativeFolderPath randomFileCopyInstruction;
      randomFileCopyInstruction.absoluteSourceFileOrFolderPath = RandomRelativeFilePath() / RandomRelativeFilePath();
      randomFileCopyInstruction.relativeDestinationFolderPath = RandomRelativeFilePath() / RandomRelativeFilePath();
      return randomFileCopyInstruction;
   }
}
