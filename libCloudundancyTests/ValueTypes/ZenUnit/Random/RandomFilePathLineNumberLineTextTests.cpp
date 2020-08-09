#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFilePathLineNumberLineText.h"

TESTS(RandomFilePathLineNumberLineTextTests)
AFACT(Random_ReturnsFilePathLineNumberWithAllFieldsNonDefault)
EVIDENCE

TEST(Random_ReturnsFilePathLineNumberWithAllFieldsNonDefault)
{
   const FilePathLineNumberLineText randomFilePathLineNumberLineText = ZenUnit::Random<FilePathLineNumberLineText>();
   IS_NOT_DEFAULT_VALUE(randomFilePathLineNumberLineText.filePath);
   IS_NOT_DEFAULT_VALUE(randomFilePathLineNumberLineText.lineNumber);
   IS_NOT_DEFAULT_VALUE(randomFilePathLineNumberLineText.lineText);
}

RUN_TESTS(RandomFilePathLineNumberLineTextTests)
