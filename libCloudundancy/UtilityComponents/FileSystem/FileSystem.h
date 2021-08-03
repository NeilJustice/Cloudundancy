#pragma once
class FileSystemTests;

namespace Utils
{
   class Asserter;
   class CharVectorAllocator;
   class ErrorCodeTranslator;

   template<typename ReturnType, typename ClassType, typename ArgType>
   class NonVoidOneArgMemberFunctionCaller;

   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgMemberFunctionCaller;

   template<typename ClassType, typename Arg1Type>
   class VoidOneArgMemberFunctionCaller;

   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCaller;

   class StopwatchFactory;

   class FileSystem
   {
      friend class ::FileSystemTests;
   private:
      // C Function Pointers
      function<int(FILE*)> _call_fclose;
      function<int(FILE*)> _call_fflush;
      function<size_t(void*, size_t, size_t, FILE*)> _call_fread;
      function<int(FILE*, long, int)> _call_fseek;
      function<long(FILE*)> _call_ftell;
      function<size_t(const void*, size_t, size_t, FILE*)> _call_fwrite;
#if defined __linux__
      function<FILE*(const char*, const char*)> _call_fopen;
#elif defined _WIN32
      function<FILE*(const wchar_t*, const wchar_t*, int)> _call_wfsopen;
#endif
      // std::filesystem Function Pointers
      using fs_copy_file_FunctionOverloadType = bool(*)(const fs::path&, const fs::path&, fs::copy_options);
      function<bool(const fs::path&, const fs::path&, fs::copy_options)> _call_fs_copy_file;

      using fs_create_directories_FunctionOverloadType = bool(*)(const fs::path&);
      function<bool(const fs::path&)> _call_fs_create_directories;

      using fs_current_path_FunctionOverloadType = void(*)(const fs::path&);
      function<void(const fs::path&)> _call_fs_current_path;

      using fs_exists_FunctionOverloadType = bool(*)(const fs::path&);
      function<bool(const fs::path&)> _call_fs_exists;

      using fs_remove_all_FunctionOverloadType = unsigned long long(*)(const fs::path&);
      function<unsigned long long(const fs::path&)> _call_fs_remove_all;
      // Function Callers
      using _caller_CreateOrOpenFileFunctionType = Utils::NonVoidOneArgMemberFunctionCaller<shared_ptr<FILE>, FileSystem, const fs::path&>;
      unique_ptr<_caller_CreateOrOpenFileFunctionType> _caller_CreateOrOpenFileFunction;

      using _caller_ReadFileBytesType = NonVoidOneArgMemberFunctionCaller<shared_ptr<const vector<char>>, FileSystem, const fs::path&>;
      unique_ptr<const _caller_ReadFileBytesType> _caller_ReadFileBytes;

      using _caller_ReadFileSizeType = Utils::NonVoidOneArgMemberFunctionCaller<size_t, FileSystem, const shared_ptr<FILE>&>;
      unique_ptr<const _caller_ReadFileSizeType> _caller_ReadFileSize;

      using _caller_ReadFileTextType = Utils::NonVoidOneArgMemberFunctionCaller<string, FileSystem, const fs::path&>;
      unique_ptr<const _caller_ReadFileTextType> _caller_ReadFileText;

      using _caller_WriteTextToOpenFileType = Utils::VoidTwoArgMemberFunctionCaller<FileSystem, const shared_ptr<FILE>&, string_view>;
      unique_ptr<const _caller_WriteTextToOpenFileType> _caller_WriteTextToOpenFile;

#if defined __linux__
      using _caller_CreateOrOpenFileOnLinuxType = Utils::NonVoidTwoArgMemberFunctionCaller<shared_ptr<FILE>, FileSystem, const fs::path&, const char*>;
      unique_ptr<const _caller_CreateOrOpenFileOnLinuxType> _caller_CreateOrOpenFileOnLinux;
#elif defined _WIN32
      using _caller_CreateOrOpenFileOnWindowsType = Utils::NonVoidTwoArgMemberFunctionCaller<shared_ptr<FILE>, FileSystem, const fs::path&, const wchar_t*>;
      unique_ptr<const _caller_CreateOrOpenFileOnWindowsType> _caller_CreateOrOpenFileOnWindows;
#endif
      // Constant Callers
      unique_ptr<const Utils::Asserter> _asserter;
      unique_ptr<const CharVectorAllocator> _charVectorAllocator;
      unique_ptr<const Utils::ErrorCodeTranslator> _errorCodeTranslator;
      unique_ptr<const StopwatchFactory> _stopwatchFactory;
   public:
      FileSystem();
      virtual ~FileSystem();
      // File Open Functions
      virtual shared_ptr<FILE> CreateFileInBinaryWriteMode(const fs::path& filePath) const;
      virtual shared_ptr<FILE> CreateOrOpenFileInBinaryAppendMode(const fs::path& filePath) const;
      virtual bool FileOrFolderExists(const fs::path& fileOrFolderPath) const;
      virtual shared_ptr<FILE> OpenFileInBinaryReadMode(const fs::path& filePath) const;
      virtual shared_ptr<FILE> OpenFileInTextReadMode(const fs::path& filePath) const;
      // Behavior Functions
      virtual void AppendTextToClosedFile(const fs::path& filePath, string_view text) const;
      virtual void CloseFile(const shared_ptr<FILE>& filePointer, const fs::path& filePath) const;
      virtual Utils::FileCopyResult CopyFileToFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
      virtual Utils::FileCopyResult CopyFileToFileLargerThan2GB(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
      virtual void CreateFileWithTextIfDoesNotExist(const fs::path& filePath, string_view fileText) const;
      virtual void DeleteFolder(const fs::path& folderPath) const;
      virtual vector<string> ReadFileLinesWhichMustBeNonEmpty(const fs::path& filePath) const;
      virtual shared_ptr<const vector<char>> ReadFileBytes(const fs::path& filePath) const;
      virtual string ReadFileText(const fs::path& filePath) const;
      virtual void SetCurrentPath(const fs::path& folderPath) const;
      virtual void ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist(const fs::path& filePath) const;
      virtual void WriteTextToOpenFile(const shared_ptr<FILE>& filePointer, string_view text) const;
      virtual void WriteBytesToOpenFile(const shared_ptr<FILE>& filePointer, const void* bytes, size_t bytesLength) const;
   private:
#if defined __linux__
      shared_ptr<FILE> CreateOrOpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const;
#elif defined _WIN32
      shared_ptr<FILE> CreateOrOpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const;
#endif
      size_t ReadFileSize(const shared_ptr<FILE>& filePointer) const;
   };
}
