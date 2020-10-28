#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFileCopyInstruction.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"

namespace ZenUnit
{
   template<>
   AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath Random<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath>()
   {
      AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath randomFileCopyInstruction;
      randomFileCopyInstruction.absoluteSourceFileOrFolderPath = RandomRelativeFilePath() / RandomRelativeFilePath();
      randomFileCopyInstruction.relativeDestinationFolderPath = RandomRelativeFilePath() / RandomRelativeFilePath();
      return randomFileCopyInstruction;
   }
}
