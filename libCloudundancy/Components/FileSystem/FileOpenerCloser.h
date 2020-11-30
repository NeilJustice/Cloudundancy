#pragma once
class Asserter;

class FileOpenerCloser
{
   friend class FileOpenerCloserTests;
private:
   // Function Callers
   function<int(FILE*)> _call_fclose;
#ifdef __linux__
   function<FILE* (const char*, const char*)> _call_fopen;
#elif _WIN32
   function<FILE* (const wchar_t*, const wchar_t*)> _call_wfopen;
#endif
   // Constant Components
   unique_ptr<const Asserter> _asserter;
public:
   FileOpenerCloser();
   virtual ~FileOpenerCloser();
   virtual FILE* CreateBinaryFileInWriteMode(const fs::path& filePath) const;
   virtual FILE* CreateTextFileInWriteMode(const fs::path& filePath) const;
   virtual FILE* OpenBinaryFileInReadMode(const fs::path& filePath) const;
   virtual FILE* OpenTextFileInReadMode(const fs::path& filePath) const;
   virtual FILE* OpenTextFileInAppendMode(const fs::path& filePath) const;
   virtual void CloseFile(FILE* filePointer) const;
private:
#ifdef __linux__
   FILE* OpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const;
#elif _WIN32
   FILE* OpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const;
#endif
   void ThrowFileOpenExceptionIfFileOpenFailed(FILE* filePointer, const fs::path& filePath) const;
};
