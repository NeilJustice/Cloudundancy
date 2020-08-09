#pragma once
class Asserter;

class FileOpenerCloser
{
   friend class FileOpenerCloserTests;
private:
   unique_ptr<const Asserter> _asserter;
#ifdef __linux__
   function<FILE*(const char*, const char*)> _call_fopen;
#elif _WIN32
   function<FILE*(const wchar_t*, const wchar_t*)> _call_wfopen;
#endif
   function<int(FILE*)> _call_fclose;
public:
   FileOpenerCloser();
   virtual ~FileOpenerCloser();
   virtual void CloseFile(FILE* filePointer) const;
   virtual FILE* OpenTextFileInReadMode(const fs::path& filePath) const;
   virtual FILE* CreateTextFileInWriteMode(const fs::path& filePath) const;
   virtual FILE* OpenBinaryFileInReadMode(const fs::path& filePath) const;
   virtual FILE* CreateBinaryFileInWriteMode(const fs::path& filePath) const;
private:
#ifdef __linux__
   virtual FILE* OpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const;
#elif _WIN32
   virtual FILE* OpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const;
#endif
   virtual void ThrowFileOpenExceptionIfFileOpenFailed(FILE* filePointer, const fs::path& filePath) const;
};
