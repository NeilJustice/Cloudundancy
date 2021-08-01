#include "pch.h"
#include "libCloudundancy/UtilityComponents/Assertion/Asserter.h"
#include "libCloudundancy/Components/ErrorHandling/ErrorCodeTranslator.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FCloseDeleter.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RawFileSystem.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/MemberFunctions/NonVoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/MemberFunctions/NonVoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/MemberFunctions/VoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/MemberFunctions/VoidTwoArgMemberFunctionCaller.h"

RawFileSystem::RawFileSystem()
   // C Function Pointers
   : _call_fclose(fclose)
   , _call_fflush(fflush)
   , _call_fread(fread)
   , _call_fseek(fseek)
   , _call_ftell(ftell)
   , _call_fwrite(fwrite)
#if defined __linux__
   , _call_fopen(::fopen)
#elif defined _WIN32
   , _call_wfsopen(_wfsopen)
#endif
   // std::filesystem Function Pointers
   , _call_fs_create_directories(static_cast<create_directories_FunctionOverloadType>(fs::create_directories))
   , _call_fs_exists(static_cast<std_filesystem_exists_FunctionOverloadType>(fs::exists))
   // Function Callers
   , _caller_CloseFile(make_unique<_caller_CloseFileType>())
   , _caller_CreateFileInBinaryWriteMode(make_unique<_caller_CreateFileInBinaryWriteModeType>())
   , _caller_ReadFileSize(make_unique<_caller_ReadFileSizeType>())
   , _caller_WriteTextToOpenFile(make_unique<_caller_WriteTextToOpenFileType>())
#if defined __linux__
   , _caller_CreateOrOpenFileOnLinux(make_unique<_caller_CreateOrOpenFileOnLinuxType>())
#elif defined _WIN32
   , _caller_CreateOrOpenFileOnWindows(make_unique<_caller_CreateOrOpenFileOnWindowsType>())
#endif
   // Constant Components
   , _asserter(make_unique<Asserter>())
   , _errorCodeTranslator(make_unique<ErrorCodeTranslator>())
{
}

RawFileSystem::~RawFileSystem()
{
}

void RawFileSystem::CloseFile(const shared_ptr<FILE>& filePointer, const fs::path& filePath) const
{
   const int fcloseReturnValue = _call_fclose(filePointer.get());
   if (fcloseReturnValue != 0)
   {
      const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
      const string exceptionMessage = String::ConcatValues(
         "fclose(filePointer) when closing file ", filePath.string(), " returned ", errnoWithDescription.first, ": ", errnoWithDescription.second);
      throw runtime_error(exceptionMessage);
   }
}

void RawFileSystem::CreateFileWithTextIfDoesNotExist(const fs::path& filePath, string_view fileText) const
{
   const bool fileExists = _call_fs_exists(filePath);
   if (!fileExists)
   {
      const shared_ptr<FILE> textFilePointer =
         _caller_CreateFileInBinaryWriteMode->CallConstMemberFunction(&RawFileSystem::CreateFileInBinaryWriteMode, this, filePath);
      _caller_WriteTextToOpenFile->CallConstMemberFunction(&RawFileSystem::WriteTextToOpenFile, this, textFilePointer, fileText);
   }
}

shared_ptr<FILE> RawFileSystem::CreateFileInBinaryWriteMode(const fs::path& filePath) const
{
#if defined __linux__
   shared_ptr<FILE> filePointer = _caller_CreateOrOpenFileOnLinux->CallConstMemberFunction(&RawFileSystem::CreateOrOpenFileOnLinux, this, filePath, "wb");
#elif defined _WIN32
   shared_ptr<FILE> filePointer = _caller_CreateOrOpenFileOnWindows->CallConstMemberFunction(&RawFileSystem::CreateOrOpenFileOnWindows, this, filePath, L"wb");
#endif
   return filePointer;
}

string RawFileSystem::ReadTextFromOpenFile(const shared_ptr<FILE>& filePointer) const
{
   const size_t fileSize = _caller_ReadFileSize->CallConstMemberFunction(&RawFileSystem::ReadFileSize, this, filePointer);
   string fileText(fileSize, 0);
   if (fileSize > 0)
   {
      const size_t numberOfBytesRead = _call_fread(const_cast<char*>(&fileText[0]), 1, fileSize, filePointer.get());
      _asserter->ThrowIfSizeTsNotEqual(fileSize, numberOfBytesRead,
         "_call_fread(const_cast<char*>(&fileText[0]), 1, fileSize, filePointer.get()) unexpectedly returned numberOfBytesRead != fileSize");
   }
   return fileText;
}

shared_ptr<FILE> RawFileSystem::OpenFileInTextReadMode(const fs::path& filePath) const
{
#if defined __linux__
   shared_ptr<FILE> filePointer = _caller_CreateOrOpenFileOnLinux->CallConstMemberFunction(&RawFileSystem::CreateOrOpenFileOnLinux, this, filePath, "r");
#elif defined _WIN32
   shared_ptr<FILE> filePointer = _caller_CreateOrOpenFileOnWindows->CallConstMemberFunction(&RawFileSystem::CreateOrOpenFileOnWindows, this, filePath, L"r");
#endif
   return filePointer;
}

void RawFileSystem::WriteTextToOpenFile(const shared_ptr<FILE>& filePointer, string_view text) const
{
   const size_t textSize = text.size();
   const size_t numberOfBytesWritten = _call_fwrite(text.data(), 1, textSize, filePointer.get());
   _asserter->ThrowIfSizeTsNotEqual(textSize, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != textSize");
   const int flushReturnValue = _call_fflush(filePointer.get());
   _asserter->ThrowIfIntsNotEqual(0, flushReturnValue, "fflush() unexpectedly did not return 0");
}

void RawFileSystem::WriteBytesToOpenFile(const shared_ptr<FILE>& filePointer, const void* bytes, size_t bytesLength) const
{
   const size_t numberOfBytesWritten = _call_fwrite(bytes, 1, bytesLength, filePointer.get());
   _asserter->ThrowIfSizeTsNotEqual(bytesLength, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != bytesLength");
   const int flushReturnValue = _call_fflush(filePointer.get());
   _asserter->ThrowIfIntsNotEqual(0, flushReturnValue, "fflush() unexpectedly did not return 0");
}

//
// Private Functions
//

#if defined __linux__

shared_ptr<FILE> RawFileSystem::CreateOrOpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const
{
   const fs::path parentDirectoryPath = filePath.parent_path();
   _call_fs_create_directories(parentDirectoryPath);
   FILE* const rawFilePointer = _call_fopen(filePath.c_str(), fileOpenMode);
   if (rawFilePointer == nullptr)
   {
      const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
      const string exceptionMessage = String::ConcatValues(
         "fopen(filePath.c_str(), fileOpenMode) returned nullptr. ",
         "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
      throw runtime_error(exceptionMessage);
   }
   shared_ptr<FILE> filePointer(rawFilePointer, FCloseDeleter());
   return filePointer;
}

#elif defined _WIN32

shared_ptr<FILE> RawFileSystem::CreateOrOpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const
{
   const fs::path parentDirectoryPath = filePath.parent_path();
   _call_fs_create_directories(parentDirectoryPath);
   FILE* const rawFilePointer = _call_wfsopen(filePath.c_str(), fileOpenMode, _SH_DENYWR);
   if (rawFilePointer == nullptr)
   {
      const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
      const string exceptionMessage = String::ConcatValues(
         "_wfsopen(filePath.c_str(), fileOpenMode, _SH_DENYWR) returned nullptr. ",
         "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
      throw runtime_error(exceptionMessage);
   }
   shared_ptr<FILE> filePointer(rawFilePointer, FCloseDeleter());
   return filePointer;
}

#endif

size_t RawFileSystem::ReadFileSize(const shared_ptr<FILE>& filePointer) const
{
   const int fseekEndReturnValue = _call_fseek(filePointer.get(), 0, SEEK_END);
   _asserter->ThrowIfIntsNotEqual(0, fseekEndReturnValue, "fseek(filePointer.get(), 0, SEEK_END) in FileSystem::FileSize() unexpectedly did not return 0");
   const long ftellReturnValue = _call_ftell(filePointer.get());
   const int fseekSetReturnValue = _call_fseek(filePointer.get(), 0, SEEK_SET);
   _asserter->ThrowIfIntsNotEqual(0, fseekSetReturnValue, "fseek(filePointer.get(), 0, SEEK_SET) in FileSystem::FileSize() unexpectedly did not return 0");
   const size_t fileSizeInBytes = static_cast<size_t>(ftellReturnValue);
   return fileSizeInBytes;
}
