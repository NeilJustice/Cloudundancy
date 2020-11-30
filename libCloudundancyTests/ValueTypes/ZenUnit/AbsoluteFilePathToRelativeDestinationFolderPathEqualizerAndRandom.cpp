#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteFilePathToRelativeDestinationFolderPath>::AssertEqual(
      const AbsoluteFilePathToRelativeDestinationFolderPath& expected,
      const AbsoluteFilePathToRelativeDestinationFolderPath& actual)
   {
      ARE_EQUAL(expected.absoluteSourceFilePath, actual.absoluteSourceFilePath);
      ARE_EQUAL(expected.relativeDestinationFolderPath, actual.relativeDestinationFolderPath);
   }

   AbsoluteFilePathToRelativeDestinationFolderPath TestableRandomAbsoluteFilePathToRelativeDestinationFolderPath(
      const ZenUnit::RandomGenerator* randomGenerator, const UtilsRandomGenerator* utilsRandomGenerator)
   {
      AbsoluteFilePathToRelativeDestinationFolderPath randomCloudundancyIniCopyInstruction;
      randomCloudundancyIniCopyInstruction.absoluteSourceFilePath = randomGenerator->FilesystemPath();
      randomCloudundancyIniCopyInstruction.relativeDestinationFolderPath = utilsRandomGenerator->RelativeFolderPath();
      return randomCloudundancyIniCopyInstruction;
   }

   template<>
   AbsoluteFilePathToRelativeDestinationFolderPath Random<AbsoluteFilePathToRelativeDestinationFolderPath>()
   {
      return TestableRandomAbsoluteFilePathToRelativeDestinationFolderPath(
         ZenUnit::RandomGenerator::Instance(), UtilsRandomGenerator::Instance());
   }
}
