#pragma once
class Asserter;

class FileOpenerCloser
{
   friend class FileOpenerCloserTests;
private:
   // Function Pointers
   function<int(FILE*)> _call_fclose;
#ifdef __linux__
   std::function<FILE* (const char*, const char*)> _call_fopen;
#elif _WIN32
   std::function<FILE* (const wchar_t*, const wchar_t*, int)> _call_wfsopen;
#endif
   // Constant Components
   unique_ptr<const Asserter> _asserter;
public:
   FileOpenerCloser();
   virtual ~FileOpenerCloser();
   virtual FILE* CreateWriteModeBinaryFile(const fs::path& filePath) const;
   virtual FILE* CreateWriteModeTextFile(const fs::path& filePath) const;
   virtual FILE* OpenReadModeBinaryFile(const fs::path& filePath) const;
   virtual FILE* OpenReadModeTextFile(const fs::path& filePath) const;
   virtual FILE* OpenAppendModeTextFile(const fs::path& filePath) const;
   virtual void CloseFile(FILE* filePointer) const;
private:
#ifdef __linux__
   FILE* OpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const;
#elif _WIN32
   FILE* OpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const;
#endif
   void ThrowFileOpenExceptionIfFileOpenFailed(FILE* filePointer, const fs::path& filePath) const;
};
