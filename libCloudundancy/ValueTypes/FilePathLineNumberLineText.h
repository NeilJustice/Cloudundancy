#pragma once

struct FilePathLineNumberLineText
{
   fs::path filePath;
   size_t lineNumber;
   string lineText;

   FilePathLineNumberLineText() noexcept;
   FilePathLineNumberLineText(const fs::path& filePath, size_t lineNumber, string_view lineText);
};
