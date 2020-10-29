#pragma once

struct AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath
{
   fs::path absoluteSourceFileOrFolderPath;
   fs::path relativeDestinationFolderPath;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath) == 80);
   #else
      static_assert(sizeof(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath) == 64);
   #endif
#endif
