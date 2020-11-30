#pragma once
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"

namespace ZenUnit
{
   template<>
   class Equalizer<FilePathLineNumberLineText>
   {
   public:
      static void AssertEqual(const FilePathLineNumberLineText& expected, const FilePathLineNumberLineText& actual);
   };

   FilePathLineNumberLineText TestableRandomFilePathLineNumberLineText(const RandomGenerator* randomGenerator);
   template<>
   FilePathLineNumberLineText Random();
}
