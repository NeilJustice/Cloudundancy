#pragma once

struct AbsoluteSourceFilePath_RelativeDestinationFolderPath
{
   fs::path absoluteSourceFilePath;
   fs::path relativeDestinationFolderPath;
};

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(AbsoluteSourceFilePath_RelativeDestinationFolderPath) == 80);
   #else
      static_assert(sizeof(AbsoluteSourceFilePath_RelativeDestinationFolderPath) == 64);
   #endif
#endif
