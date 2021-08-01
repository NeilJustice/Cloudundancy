#pragma once
class RawFileSystemTests;

class Asserter;
class ErrorCodeTranslator;

template<typename ReturnType, typename ClassType, typename ArgType>
class NonVoidOneArgMemberFunctionCaller;

template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCaller;

template<typename ClassType, typename Arg1Type>
class VoidOneArgMemberFunctionCaller;

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;

class RawFileSystem
{
   friend class ::RawFileSystemTests;
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
   using create_directories_FunctionOverloadType = bool(*)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_create_directories;
   using std_filesystem_exists_FunctionOverloadType = bool(*)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_exists;
   // Function Callers
   using _caller_CloseFileType = VoidTwoArgMemberFunctionCaller<RawFileSystem, const shared_ptr<FILE>&, const fs::path&>;
   unique_ptr<const _caller_CloseFileType> _caller_CloseFile;

   using _caller_CreateFileInBinaryWriteModeType = NonVoidOneArgMemberFunctionCaller<shared_ptr<FILE>, RawFileSystem, const fs::path&>;
   unique_ptr<_caller_CreateFileInBinaryWriteModeType> _caller_CreateFileInBinaryWriteMode;

   using _caller_ReadFileSizeType = NonVoidOneArgMemberFunctionCaller<size_t, RawFileSystem, const shared_ptr<FILE>&>;
   unique_ptr<const _caller_ReadFileSizeType> _caller_ReadFileSize;

   using _caller_WriteTextToOpenFileType = VoidTwoArgMemberFunctionCaller<RawFileSystem, const shared_ptr<FILE>&, string_view>;
   unique_ptr<const _caller_WriteTextToOpenFileType> _caller_WriteTextToOpenFile;

#if defined __linux__
   using _caller_CreateOrOpenFileOnLinuxType = NonVoidTwoArgMemberFunctionCaller<shared_ptr<FILE>, RawFileSystem, const fs::path&, const char*>;
   unique_ptr<const _caller_CreateOrOpenFileOnLinuxType> _caller_CreateOrOpenFileOnLinux;
#elif defined _WIN32
   using _caller_CreateOrOpenFileOnWindowsType = NonVoidTwoArgMemberFunctionCaller<shared_ptr<FILE>, RawFileSystem, const fs::path&, const wchar_t*>;
   unique_ptr<const _caller_CreateOrOpenFileOnWindowsType> _caller_CreateOrOpenFileOnWindows;
#endif
   // Constant Callers
   unique_ptr<const Asserter> _asserter;
   unique_ptr<const ErrorCodeTranslator> _errorCodeTranslator;
public:
   RawFileSystem();
   virtual ~RawFileSystem();
   virtual void CloseFile(const shared_ptr<FILE>& filePointer, const fs::path& filePath) const;
   virtual void CreateFileWithTextIfDoesNotExist(const fs::path& filePath, string_view fileText) const;
   virtual shared_ptr<FILE> CreateFileInBinaryWriteMode(const fs::path& filePath) const;
   virtual shared_ptr<FILE> CreateOrOpenFileInBinaryAppendMode(const fs::path& filePath) const;
   virtual string ReadTextFromOpenFile(const shared_ptr<FILE>& filePointer, const fs::path& filePath) const;
   virtual shared_ptr<FILE> OpenFileInBinaryReadMode(const fs::path& filePath) const;
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
