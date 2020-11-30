#pragma once
class Asserter;
class CharVectorAllocator;
class FileSystemTests;
class FileOpenerCloser;
template<typename ReturnType, typename ClassType, typename ArgType>
class NonVoidOneArgMemberFunctionCaller;
class Stopwatch;

int* GetLinuxErrno();

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
   using CopyFileOverloadType = bool(*)(const fs::path&, const fs::path&, fs::copy_options);
   using CurrentPathOverloadType = void(*)(const fs::path&);
   using CreateDirectoriesOverloadType = bool(*)(const fs::path&);
   using ExistsOverloadType = bool(*)(const fs::path&);
   using FileSizeOverloadType = size_t(*)(const fs::path&);
   using RemoveAllOverloadType = uintmax_t(*)(const fs::path&);
   function<bool(const fs::path&, const fs::path&, fs::copy_options)> _call_fs_copy_file;
   function<void(const fs::path&)> _call_fs_current_path;
   bool(*_call_fs_create_directories_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_create_directories;
   bool(*_call_fs_exists_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_exists;
   function<size_t(const fs::path&)> _call_fs_file_size;
   function<uintmax_t(const fs::path&)> _call_fs_remove_all;

   // Function Callers
   using _caller_FileSize_Type = NonVoidOneArgMemberFunctionCaller<size_t, FileSystem, FILE*>;
   unique_ptr<const _caller_FileSize_Type> _caller_FileSize;

   using _caller_ReadFileBytes_Type = NonVoidOneArgMemberFunctionCaller<vector<char>, FileSystem, const fs::path&>;
   unique_ptr<const _caller_ReadFileBytes_Type> _caller_ReadFileBytes;

   using _caller_ReadFileText_Type = NonVoidOneArgMemberFunctionCaller<string, FileSystem, const fs::path&>;
   unique_ptr<const _caller_ReadFileText_Type> _caller_ReadFileText;

   // Constant Components
   unique_ptr<const Asserter> _asserter;
   unique_ptr<const CharVectorAllocator> _charVectorAllocator;
   unique_ptr<const FileOpenerCloser> _fileOpenerCloser;

   // Mutable Components
   unique_ptr<Stopwatch> _stopwatch;
public:
   FileSystem();
   virtual ~FileSystem();

   // File Or Folder Existence Checks
   virtual bool FileOrFolderExists(const fs::path& fileOrFolderPath) const;
   virtual void ThrowIfFilePathIsNotEmptyAndDoesNotExist(const fs::path& filePath) const;

   // File Reads
   virtual vector<char> ReadFileBytes(const fs::path& filePath) const;
   virtual string ReadFileText(const fs::path& filePath) const;
   virtual vector<string> ReadFileLinesWhichMustBeNonEmpty(const fs::path& filePath) const;

   // File Copies
   virtual FileCopyResult TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   virtual FileCopyResult TryCopyFileWithStdFilesystemCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   virtual bool IsFileSizeGreaterThanOrEqualTo2GB(const fs::path& filePath) const;

   // File Writes
   virtual void AppendTimestampedText(const fs::path& filePath, string_view text) const;
   virtual void WriteTextFile(const fs::path& filePath, string_view text) const;

   // Misc
   virtual void DeleteFolder(const fs::path& folderPath) const;
   virtual void SetCurrentPath(const fs::path& folderPath) const;
private:
   size_t FileSize(FILE* filePointer) const;
};
