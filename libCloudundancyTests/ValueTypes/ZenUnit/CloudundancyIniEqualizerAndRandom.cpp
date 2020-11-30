#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyIni>::AssertEqual(
      const CloudundancyIni& expectedCloudundancyIni, const CloudundancyIni& actualCloudundancyIni)
   {
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.destinationFolderPaths, actualCloudundancyIni.destinationFolderPaths);
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.cloudundancyIniCopyInstructions, actualCloudundancyIni.cloudundancyIniCopyInstructions);
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.fileSubpathsToNotCopy, actualCloudundancyIni.fileSubpathsToNotCopy);
   }

   CloudundancyIni TestableRandomCloudundancyIni(
      const ZenUnit::RandomGenerator* /*randomGenerator*/, const UtilsRandomGenerator* /*utilsRandomGenerator*/)
   {
      CloudundancyIni randomCloudundancyIni;
      //randomCloudundancyIni.destinationFolderPaths = RandomRelativeFolderPaths();
      //randomCloudundancyIni.cloudundancyIniCopyInstructions =
      //   ZenUnit::RandomNonEmptyVector<CloudundancyIniCopyInstruction>();
      //randomCloudundancyIni.fileSubpathsToNotCopy = randomGenerator->StringVector();
      return randomCloudundancyIni;
   }

   template<>
   CloudundancyIni Random()
   {
      return TestableRandomCloudundancyIni(ZenUnit::RandomGenerator::Instance(), UtilsRandomGenerator::Instance());
   }
}
