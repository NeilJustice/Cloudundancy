#pragma once

struct FilePathLineNumberLineText
{
   fs::path filePath;
   size_t lineNumber;
   string lineText;

   FilePathLineNumberLineText() noexcept;
   FilePathLineNumberLineText(const fs::path& filePath, size_t lineNumber, string_view lineText);
};

#ifdef _WIN32
#ifdef _DEBUG
static_assert(sizeof(FilePathLineNumberLineText) == 88);
#else
static_assert(sizeof(FilePathLineNumberLineText) == 72);
#endif
#elifdef __linux__
static_assert(sizeof(FilePathLineNumberLineText) == 80);
#endif
