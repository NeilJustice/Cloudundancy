#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/RandomCloudundancyIni.h"

TESTS(RandomCloudundancyIniTests)
AFACT(RandomCloudundancyIni_ReturnsCloudunancyIniWithAllFieldsNonDefault)
EVIDENCE

TEST(RandomCloudundancyIni_ReturnsCloudunancyIniWithAllFieldsNonDefault)
{
   const CloudundancyIni randomCloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //IS_NOT_DEFAULT_VALUE(randomCloudundancyIni.destinationFolderPaths);
   IS_NOT_EMPTY(randomCloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths);
   IS_NOT_EMPTY(randomCloudundancyIni.fileSubpathsToNotCopy);
}

RUN_TESTS(RandomCloudundancyIniTests)
