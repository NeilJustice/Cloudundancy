#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FilePathLineNumberLineTextEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FilePathLineNumberLineText>::AssertEqual(
      const FilePathLineNumberLineText& expected, const FilePathLineNumberLineText& actual)
   {
      ARE_EQUAL(expected.filePath, actual.filePath);
      ARE_EQUAL(expected.lineNumber, actual.lineNumber);
      ARE_EQUAL(expected.lineText, actual.lineText);
   }

   FilePathLineNumberLineText TestableRandomFilePathLineNumberLineText(const RandomGenerator* randomGenerator)
   {
      FilePathLineNumberLineText randomFilePathLineNumberLineText;
      randomFilePathLineNumberLineText.filePath = randomGenerator->FilesystemPath();
      randomFilePathLineNumberLineText.lineNumber = randomGenerator->SizeT();
      randomFilePathLineNumberLineText.lineText = randomGenerator->String();
      return randomFilePathLineNumberLineText;
   }

   template<>
   FilePathLineNumberLineText Random()
   {
      return TestableRandomFilePathLineNumberLineText(RandomGenerator::Instance());
   }
}
