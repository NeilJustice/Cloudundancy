#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/RandomAbsoluteFileOrFolderPathToRelativeFolderPath.h"

TESTS(RandomAbsoluteFileOrFolderPathToRelativeFolderPathTests)
AFACT(Random_ReturnsFileCopyInstructionWithAllFieldsNonDefault)
EVIDENCE

TEST(Random_ReturnsFileCopyInstructionWithAllFieldsNonDefault)
{
   const AbsoluteFileOrFolderPathToRelativeFolderPath randomFileCopyInstruction =
      ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   IS_NOT_DEFAULT_VALUE(randomFileCopyInstruction.absoluteSourceFileOrFolderPath);
   IS_NOT_DEFAULT_VALUE(randomFileCopyInstruction.relativeDestinationFolderPath);
}

RUN_TESTS(RandomAbsoluteFileOrFolderPathToRelativeFolderPathTests)