#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniCopyInstructionEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyIniCopyInstruction>::AssertEqual(
      const CloudundancyIniCopyInstruction& expectedCloudundancyIniCopyInstruction,
      const CloudundancyIniCopyInstruction& actualCloudundancyIniCopyInstruction)
   {
      ARE_EQUAL(
         expectedCloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath,
         actualCloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
      ARE_EQUAL(
         expectedCloudundancyIniCopyInstruction.relativeDestinationFolderPath,
         actualCloudundancyIniCopyInstruction.relativeDestinationFolderPath);
   }

   CloudundancyIniCopyInstruction TestableRandomCloudundancyIniCopyInstruction(const UtilsRandomGenerator* utilsRandomGenerator)
   {
      CloudundancyIniCopyInstruction randomFileCopyInstruction;
      randomFileCopyInstruction.absoluteSourceFileOrFolderPath = utilsRandomGenerator->RelativeFilePath();
      randomFileCopyInstruction.relativeDestinationFolderPath = utilsRandomGenerator->RelativeFolderPath();
      return randomFileCopyInstruction;
   }

   template<>
   CloudundancyIniCopyInstruction Random<CloudundancyIniCopyInstruction>()
   {
      return TestableRandomCloudundancyIniCopyInstruction(UtilsRandomGenerator::Instance());
   }
}
