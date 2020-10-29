#pragma once

struct AbsoluteFilePathToRelativeDestinationFolderPath
{
   fs::path absoluteSourceFilePath;
   fs::path relativeDestinationFolderPath;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(AbsoluteFilePathToRelativeDestinationFolderPath) == 80);
   #else
      static_assert(sizeof(AbsoluteFilePathToRelativeDestinationFolderPath) == 64);
   #endif
#endif
