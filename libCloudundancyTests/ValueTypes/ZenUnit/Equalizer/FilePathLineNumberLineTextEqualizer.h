#pragma once
struct FilePathLineNumberLineText;

namespace ZenUnit
{
   template<>
   class Equalizer<FilePathLineNumberLineText>
   {
   public:
      static void AssertEqual(const FilePathLineNumberLineText& expected, const FilePathLineNumberLineText& actual);
   };
}
