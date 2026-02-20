#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileSystemPather.h"

namespace Utils
{
   FileSystemPather::FileSystemPather()
      // Function Pointers
      : _call_fs_absolute_as_assignable_function_overload_pointer(static_cast<fs_absolute_function_overload_type>(fs::absolute))
      , _call_fs_absolute(_call_fs_absolute_as_assignable_function_overload_pointer)

      , _call_fs_is_regular_file_as_assignable_function_overload_pointer(fs::is_regular_file)
      , _call_fs_is_regular_file(_call_fs_is_regular_file_as_assignable_function_overload_pointer)
   {
   }

   FileSystemPather::~FileSystemPather()
   {
   }

   // Exceptions

   void FileSystemPather::ThrowIfFileDoesNotExist(const fs::path& filePath) const
   {
      const bool isRegularFileThatExists = _call_fs_is_regular_file(filePath);
      [[unlikely]] if (!isRegularFileThatExists)
      {
         throw FileNotFoundException(filePath);
      }
   }

   // File and Folder Paths

   fs::path FileSystemPather::GetAbsoluteFileOrFolderPath(const fs::path& fileOrFolderPath) const
   {
      if (fileOrFolderPath.empty())
      {
         return fileOrFolderPath;
      }
      fs::path absoluteFileOrFolderPath = _call_fs_absolute(fileOrFolderPath);
      return absoluteFileOrFolderPath;
   }
}
