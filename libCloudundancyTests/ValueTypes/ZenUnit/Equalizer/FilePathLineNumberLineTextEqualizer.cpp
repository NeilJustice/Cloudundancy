#include "pch.h"
#include "FilePathLineNumberLineTextEqualizer.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"

namespace ZenUnit
{
   void Equalizer<FilePathLineNumberLineText>::AssertEqual(
      const FilePathLineNumberLineText& expected, const FilePathLineNumberLineText& actual)
   {
      ARE_EQUAL(expected.filePath, actual.filePath);
      ARE_EQUAL(expected.lineNumber, actual.lineNumber);
      ARE_EQUAL(expected.lineText, actual.lineText);
   }
}
