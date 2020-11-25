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
   // Constant Components
   unique_ptr<const Asserter> _asserter;
   unique_ptr<const CharVectorAllocator> _charVectorAllocator;
   unique_ptr<const FileOpenerCloser> _fileOpenerCloser;

   // Function Pointers
   function<int*()> _call_errno;
   function<size_t(void*, size_t, size_t, FILE*)> _call_fread;
   function<int(FILE*, long, int)> _call_fseek;
   function<void(const fs::path&)> _call_fs_current_path;
   bool(*_call_fs_create_directories_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_create_directories;
   function<size_t(const void*, size_t, size_t, FILE*)> _call_fwrite;
   function<long(FILE*)> _call_ftell;
   function<uintmax_t(const fs::path&)> _call_std_filesystem_remove_all;
   bool(*_call_std_filesystem_exists_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_std_filesystem_exists;

   // Function Callers
   using _caller_ReadFileText_Type = NonVoidOneArgMemberFunctionCaller<string, FileSystem, const fs::path&>;
   unique_ptr<const _caller_ReadFileText_Type> _caller_ReadFileText;

   using _caller_ReadFileBytes_Type = NonVoidOneArgMemberFunctionCaller<vector<char>, FileSystem, const fs::path&>;
   unique_ptr<const _caller_ReadFileBytes_Type> _caller_ReadFileBytes;

   using _caller_ReadFileSize_Type = NonVoidOneArgMemberFunctionCaller<size_t, FileSystem, FILE*>;
   unique_ptr<const _caller_ReadFileSize_Type> _caller_ReadFileSize;

   // Mutable Components
   unique_ptr<Stopwatch> _stopwatch;
public:
   FileSystem();
   virtual ~FileSystem();
   virtual void DeleteFolder(const fs::path& folderPath) const;
   virtual bool FileOrFolderExists(const fs::path& fileOrFolderPath) const;
   virtual vector<string> ReadFileLinesWhichMustBeNonEmpty(const fs::path& filePath) const;
   virtual string ReadFileText(const fs::path& filePath) const;
   virtual vector<char> ReadFileBytes(const fs::path& filePath) const;
   virtual void SetCurrentPath(const fs::path& folderPath) const;
   virtual void ThrowIfFilePathIsNotEmptyAndDoesNotExist(const fs::path& filePath) const;
   virtual FileCopyResult TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   virtual void WriteTextFile(const fs::path& filePath, string_view text) const;
private:
   size_t ReadFileSize(FILE* filePointer) const;
};
