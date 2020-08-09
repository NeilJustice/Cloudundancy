#include "pch.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"

FilePathLineNumberLineText::FilePathLineNumberLineText() noexcept
   : lineNumber(0)
{
}

FilePathLineNumberLineText::FilePathLineNumberLineText(const fs::path& filePath, size_t lineNumber, string_view lineText)
   : filePath(filePath)
   , lineNumber(lineNumber)
   , lineText(lineText)
{
}
