#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FilesystemPathRandom.h"

namespace ZenUnit
{
   template<>
   FilePathLineNumberLineText Random()
   {
      FilePathLineNumberLineText randomFilePathLineNumberLineText;
      randomFilePathLineNumberLineText.filePath = RandomRelativeFilePath();
      randomFilePathLineNumberLineText.lineNumber = ZenUnit::RandomNon0<size_t>();
      randomFilePathLineNumberLineText.lineText = ZenUnit::Random<string>();
      return randomFilePathLineNumberLineText;
   }
}
