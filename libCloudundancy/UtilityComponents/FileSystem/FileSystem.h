#pragma once
class Asserter;
class CharVectorAllocator;
class FileSystemTests;
class FileOpenerCloser;
template<typename ReturnType, typename ClassType, typename ArgType>
class NonVoidOneArgMemberFunctionCaller;
template<typename ClassType, typename ElementType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacher;
class RecursiveDirectoryIterator;
template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;
class Stopwatch;
class Watch;

class FileSystem
{
   friend class FileSystemTests;
private:
   // C File Function Pointers
   function<int*()> _call_errno;
   function<size_t(void*, size_t, size_t, FILE*)> _call_fread;
   function<int(FILE*, long, int)> _call_fseek;
   function<long(FILE*)> _call_ftell;
   function<size_t(const void*, size_t, size_t, FILE*)> _call_fwrite;

   // std::filesystem Function Pointers
   using FSCopyFileFunctionOverloadType = bool(*)(const fs::path&, const fs::path&, fs::copy_options);
   function<bool(const fs::path&, const fs::path&, fs::copy_options)> _call_fs_copy_file;

   using FSCurrentPathFunctionOverloadType = void(*)(const fs::path&);
   function<void(const fs::path&)> _call_fs_current_path;

   using CreateDirectoriesOverloadType = bool(*)(const fs::path&);
   bool(*_call_fs_create_directories_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_create_directories;

   using FSRemoveAllFunctionOverloadType = unsigned long long(*)(const fs::path&);
   function<unsigned long long(const fs::path&)> _call_fs_remove_all;

   using FSExistsFunctionOverloadType = bool(*)(const fs::path&);
   bool(*_call_fs_exists_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_exists;

   using FSFileSizeFunctionOverloadType = size_t(*)(const fs::path&);
   function<size_t(const fs::path&)> _call_fs_file_size;

   // Function Callers
   using _caller_FileSize_Type = NonVoidOneArgMemberFunctionCaller<size_t, FileSystem, FILE*>;
   unique_ptr<const _caller_FileSize_Type> _caller_FileSize;

   using _caller_FileSystem_DeleteFolderContentsExceptForFileNameType = OneExtraArgMemberFunctionForEacher<FileSystem, fs::path, string_view>;
   unique_ptr<const _caller_FileSystem_DeleteFolderContentsExceptForFileNameType> _caller_FileSystem_DeleteFolderContentsExceptForFileName;

   using _caller_ReadFileBytes_Type = NonVoidOneArgMemberFunctionCaller<shared_ptr<const vector<char>>, FileSystem, const fs::path&>;
   unique_ptr<const _caller_ReadFileBytes_Type> _caller_ReadFileBytes;

   using _caller_ReadFileText_Type = NonVoidOneArgMemberFunctionCaller<string, FileSystem, const fs::path&>;
   unique_ptr<const _caller_ReadFileText_Type> _caller_ReadFileText;

   using _caller_CreateTextFileType = VoidTwoArgMemberFunctionCaller<FileSystem, const fs::path&, string_view>;
   unique_ptr<const _caller_CreateTextFileType> _caller_CreateTextFile;

   // Constant Components
   unique_ptr<const Asserter> _asserter;
   unique_ptr<const Console> _console;
   unique_ptr<const CharVectorAllocator> _charVectorAllocator;
   unique_ptr<const FileOpenerCloser> _fileOpenerCloser;

   // Mutable Components
   unique_ptr<RecursiveDirectoryIterator> _recursiveDirectoryIterator;
   unique_ptr<Stopwatch> _stopwatch;
public:
   FileSystem();
   virtual ~FileSystem();

   // File Or Folder Existence Checks
   virtual bool FileOrFolderExists(const fs::path& fileOrFolderPath) const;
   virtual void ThrowIfFilePathIsNotEmptyAndDoesNotExist(const fs::path& filePath) const;

   // File Reads
   virtual shared_ptr<const vector<char>> ReadFileBytes(const fs::path& filePath) const;
   virtual string ReadFileText(const fs::path& filePath) const;
   virtual vector<string> ReadFileLinesWhichMustBeNonEmpty(const fs::path& filePath) const;

   // File Copies
   virtual FileCopyResult TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   virtual FileCopyResult TryCopyFileWithStdFilesystemCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   virtual bool IsFileSizeGreaterThanOrEqualTo2GB(const fs::path& filePath) const;

   // File Writes
   virtual void AppendText(const fs::path& filePath, string_view text) const;
   virtual void CreateTextFile(const fs::path& filePath, string_view text) const;

   // Misc
   virtual void DeleteFolder(const fs::path& folderPath) const;
   virtual void DeleteFolderContentsExceptForFileName(const fs::path& folderPath, string_view exceptFileName) const;
   virtual void DeleteFoldersExceptForFile(const vector<fs::path>& folderPaths, string_view exceptFileName) const;
   virtual void SetCurrentPath(const fs::path& folderPath) const;
private:
   size_t FileSize(FILE* fileHandle) const;
};
