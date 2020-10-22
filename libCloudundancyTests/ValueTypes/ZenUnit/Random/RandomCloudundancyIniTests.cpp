#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyIni.h"

TESTS(RandomCloudundancyIniTests)
AFACT(Random_ReturnsCloudunancyIniWithAllFieldsNonDefault)
EVIDENCE

TEST(Random_ReturnsCloudunancyIniWithAllFieldsNonDefault)
{
   const CloudundancyIni randomCloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //IS_NOT_DEFAULT_VALUE(randomCloudundancyIni.destinationFolderPaths);
   //IS_NOT_EMPTY(randomCloudundancyIni.fileCopyInstructions);
   //IS_NOT_DEFAULT_VALUE(randomCloudundancyIni.fileSubpathsToNotCopy);
}

RUN_TESTS(RandomCloudundancyIniTests)
