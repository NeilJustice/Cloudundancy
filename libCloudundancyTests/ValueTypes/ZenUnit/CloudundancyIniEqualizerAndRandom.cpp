#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyIni>::AssertEqual(
      const CloudundancyIni& expectedCloudundancyIni, const CloudundancyIni& actualCloudundancyIni)
   {
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.iniFileLines, actualCloudundancyIni.iniFileLines);
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.destinationFolderPaths, actualCloudundancyIni.destinationFolderPaths);
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.cloudundancyIniCopyInstructions, actualCloudundancyIni.cloudundancyIniCopyInstructions);
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.fileSubpathsToIgnore, actualCloudundancyIni.fileSubpathsToIgnore);
   }

   CloudundancyIni TestableRandomCloudundancyIni(const ZenUnit::RandomGenerator* randomGenerator)
   {
      CloudundancyIni randomCloudundancyIni;
      randomCloudundancyIni.iniFileLines = randomGenerator->StringVector();
      randomCloudundancyIni.destinationFolderPaths = randomGenerator->FilesystemPathVector();
      const size_t cloudundancyIniCopyInstructionsSize = randomGenerator->SizeTBetween(0, 2);
      randomCloudundancyIni.cloudundancyIniCopyInstructions.resize(cloudundancyIniCopyInstructionsSize);
      for (size_t i = 0; i < randomCloudundancyIni.cloudundancyIniCopyInstructions.size(); ++i)
      {
         randomCloudundancyIni.cloudundancyIniCopyInstructions[i] = ZenUnit::Random<CloudundancyIniCopyInstruction>();
      }
      randomCloudundancyIni.fileSubpathsToIgnore = randomGenerator->StringVector();
      return randomCloudundancyIni;
   }

   template<>
   CloudundancyIni Random()
   {
      return TestableRandomCloudundancyIni(ZenUnit::RandomGenerator::Instance());
   }
}
