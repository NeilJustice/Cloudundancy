#pragma once
class FileSystemPatherTests;

namespace Utils
{
   class FileSystemPather
   {
      friend class ::FileSystemPatherTests;
   private:
      // Function Pointers
      using fs_absolute_function_overload_type = fs::path(*)(const fs::path&);
      fs::path(*_call_fs_absolute_as_assignable_function_overload_pointer)(const fs::path&);
      function<fs::path(const fs::path&)> _call_fs_absolute;

      using IsRegularFileOverloadType = bool(*)(const fs::path&);
      bool(*_call_fs_is_regular_file_as_assignable_function_overload_pointer)(const fs::path&);
      function<bool(const fs::path&)> _call_fs_is_regular_file;
   public:
      FileSystemPather();
      virtual ~FileSystemPather();

      // Exceptions
      virtual void ThrowIfFileDoesNotExist(const fs::path& filePath) const;

      // File and Folder Paths
      virtual fs::path GetAbsoluteFileOrFolderPath(const fs::path& fileOrFolderPath) const;
   };
}
