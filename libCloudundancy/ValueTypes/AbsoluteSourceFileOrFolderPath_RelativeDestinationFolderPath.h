#pragma once

struct AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath
{
   fs::path absoluteSourceFileOrFolderPath;
   fs::path relativeDestinationFolderPath;
};

//template<int N>
//struct _
//{
//   operator char()
//   {
//      return N + 256;
//}
//};
//
//char(_<sizeof(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath)>());

//#ifdef _WIN32
//#ifdef _DEBUG
//static_assert(sizeof(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath) == 0);
//#else
////static_assert(sizeof() == 0);
//#endif
//#endif