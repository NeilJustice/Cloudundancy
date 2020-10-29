#pragma once

struct AbsoluteFileOrFolderPathToRelativeFolderPath
{
   fs::path absoluteSourceFileOrFolderPath;
   fs::path relativeDestinationFolderPath;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(AbsoluteFileOrFolderPathToRelativeFolderPath) == 80);
   #else
      static_assert(sizeof(AbsoluteFileOrFolderPathToRelativeFolderPath) == 64);
   #endif
#endif
