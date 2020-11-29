#include "pch.h"
#include "libCloudundancy/Components/Assertion/Asserter.h"
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/Memory/CharVectorAllocator.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/FunctionCallers/MemberFunctions/NonVoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/StaticUtilities/Errno.h"

#ifdef __linux__
int* GetLinuxErrno()
{
   return &errno;
}
#endif

FileSystem::FileSystem()
   // C File Function Pointers
#ifdef __linux__
   : _call_errno(GetLinuxErrno)
#elif _WIN32
   : _call_errno(::_errno)
#endif
   , _call_fread(::fread)
   , _call_fseek(::fseek)
   , _call_ftell(::ftell)
   , _call_fwrite(::fwrite)
   // std::filesystem Function Pointers
   , _call_fs_copy_file(static_cast<CopyFileOverloadType>(fs::copy_file))
   , _call_fs_current_path(static_cast<void(*)(const fs::path&)>(fs::current_path))
   , _call_fs_create_directories_as_assignable_function_overload_pointer(fs::create_directories)
   , _call_fs_exists_as_assignable_function_overload_pointer(fs::exists)
   , _call_fs_file_size(static_cast<FileSizeOverloadType>(fs::file_size))
   , _call_fs_remove_all(static_cast<RemoveAllOverloadType>(fs::remove_all))
   // Function Callers
   , _caller_FileSize(make_unique<_caller_FileSize_Type>())
   , _caller_ReadFileBytes(make_unique<_caller_ReadFileBytes_Type>())
   , _caller_ReadFileText(make_unique< _caller_ReadFileText_Type>())
   // Constant Components
   , _asserter(make_unique<Asserter>())
   , _charVectorAllocator(make_unique<CharVectorAllocator>())
   , _fileOpenerCloser(make_unique<FileOpenerCloser>())
   // Mutable Components
   , _stopwatch(make_unique<Stopwatch>())
{
   _call_fs_create_directories = _call_fs_create_directories_as_assignable_function_overload_pointer;
   _call_fs_exists = _call_fs_exists_as_assignable_function_overload_pointer;
}

FileSystem::~FileSystem()
{
}

// File Or Folder Existence Checks

bool FileSystem::FileOrFolderExists(const fs::path& fileOrFolderPath) const
{
   const bool fileOrFolderExists = _call_fs_exists(fileOrFolderPath);
   return fileOrFolderExists;
}

void FileSystem::ThrowIfFilePathIsNotEmptyAndDoesNotExist(const fs::path& filePath) const
{
   if (!filePath.empty())
   {
      const bool filePathExists = _call_fs_exists(filePath);
      if (!filePathExists)
      {
         throw FileSystemException(FileSystemExceptionType::FileDoesNotExist, filePath);
      }
   }
}

// File Reads

vector<char> FileSystem::ReadFileBytes(const fs::path& filePath) const
{
   FILE* const readModeBinaryFilePointer = _fileOpenerCloser->OpenBinaryFileInReadMode(filePath);
   const size_t fileSizeInBytes = _caller_FileSize->CallConstMemberFunction(
      &FileSystem::FileSize, this, readModeBinaryFilePointer);
   if (fileSizeInBytes == 0)
   {
      _fileOpenerCloser->CloseFile(readModeBinaryFilePointer);
      return {};
   }
   const unique_ptr<vector<char>> fileBytesBuffer(_charVectorAllocator->NewCharVector(fileSizeInBytes));
   const size_t numberOfBytesRead = _call_fread(&(*fileBytesBuffer)[0], 1, fileSizeInBytes, readModeBinaryFilePointer);
   _asserter->ThrowIfSizeTsNotEqual(fileSizeInBytes, numberOfBytesRead,
      "fread() in FileSystem::ReadBytes() unexpectedly did not return fileSizeInBytes");
   _fileOpenerCloser->CloseFile(readModeBinaryFilePointer);
   const vector<char> fileBytes(*fileBytesBuffer);
   return fileBytes;
}

string FileSystem::ReadFileText(const fs::path& filePath) const
{
   FILE* const readModeTextFilePointer = _fileOpenerCloser->OpenTextFileInReadMode(filePath);
   const size_t fileSizeInBytes = _caller_FileSize->CallConstMemberFunction(
      &FileSystem::FileSize, this, readModeTextFilePointer);
   if (fileSizeInBytes == 0)
   {
      _fileOpenerCloser->CloseFile(readModeTextFilePointer);
      return {};
   }
   const unique_ptr<vector<char>> fileTextBuffer(_charVectorAllocator->NewCharVector(fileSizeInBytes));
   _call_fread(&(*fileTextBuffer)[0], 1, fileSizeInBytes, readModeTextFilePointer);
   _fileOpenerCloser->CloseFile(readModeTextFilePointer);
   const string fileText(&(*fileTextBuffer)[0]);
   return fileText;
}

vector<string> FileSystem::ReadFileLinesWhichMustBeNonEmpty(const fs::path& filePath) const
{
   const string fileText = _caller_ReadFileText->CallConstMemberFunction(&FileSystem::ReadFileText, this, filePath);
   if (fileText.empty())
   {
      throw FileSystemException(FileSystemExceptionType::FileCannotBeEmpty, filePath);
   }
   istringstream fileTextIStringStream(fileText);
   vector<string> fileLines;
   string currentFileLine;
   while (getline(fileTextIStringStream, currentFileLine))
   {
      fileLines.push_back(currentFileLine);
   }
   return fileLines;
}

// File Copiies

FileCopyResult FileSystem::TryCopyFile(
   const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
{
   _stopwatch->Start();
   const vector<char> sourceFileBytes = _caller_ReadFileBytes->CallConstMemberFunction(
      &FileSystem::ReadFileBytes, this, sourceFilePath);
   try
   {
      const fs::path parentPathOfDestinationFilePath = destinationFilePath.parent_path();
      _call_fs_create_directories(parentPathOfDestinationFilePath);
   }
   catch (const fs::filesystem_error& ex)
   {
      FileCopyResult failedFileCopyResult;
      failedFileCopyResult.copySucceeded = false;
      failedFileCopyResult.sourceFilePath = sourceFilePath;
      failedFileCopyResult.destinationFilePath = destinationFilePath;
      const char* const copyFailureReason = ex.what();
      failedFileCopyResult.copyFailureReason = copyFailureReason;
      failedFileCopyResult.durationInMilliseconds = _stopwatch->StopAndGetElapsedMilliseconds();
      return failedFileCopyResult;
   }
   FILE* const writeModeDestinationBinaryFilePointer = _fileOpenerCloser->CreateBinaryFileInWriteMode(destinationFilePath);
   const size_t sourceFileBytesSize = sourceFileBytes.size();
   size_t numberOfBytesWritten = 0;
   if (sourceFileBytesSize > 0)
   {
      numberOfBytesWritten = _call_fwrite(&sourceFileBytes[0], 1, sourceFileBytesSize, writeModeDestinationBinaryFilePointer);
   }
   _fileOpenerCloser->CloseFile(writeModeDestinationBinaryFilePointer);
   _asserter->ThrowIfSizeTsNotEqual(sourceFileBytesSize, numberOfBytesWritten,
      "fwrite() in FileSystem::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) unexpectedly returned numberOfBytesWritten != sourceFileBytesSize");
   FileCopyResult successFileCopyResult;
   successFileCopyResult.sourceFilePath = sourceFilePath;
   successFileCopyResult.destinationFilePath = destinationFilePath;
   successFileCopyResult.copySucceeded = true;
   successFileCopyResult.durationInMilliseconds = _stopwatch->StopAndGetElapsedMilliseconds();
   return successFileCopyResult;
}

FileCopyResult FileSystem::TryCopyFileWithStdFilesystemCopyFile(
   const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
{
   _stopwatch->Start();
   FileCopyResult fileCopyResult;
   fileCopyResult.sourceFilePath = sourceFilePath;
   fileCopyResult.destinationFilePath = destinationFilePath;
   // try
   fileCopyResult.copySucceeded = _call_fs_copy_file(
      sourceFilePath, destinationFilePath, fs::copy_options::overwrite_existing);
   // catch (const fs::filesystem_error& ex)
   // fileCopyResult.errorMessage
   fileCopyResult.durationInMilliseconds = _stopwatch->StopAndGetElapsedMilliseconds();
   return fileCopyResult;
}

bool FileSystem::IsFileSizeGreaterThanOrEqualTo2GB(const fs::path& filePath) const
{
   const size_t fileSizeInBytes = _call_fs_file_size(filePath);
   constexpr size_t NumberOfBytesIn2GB = 2ull * 1024ull * 1024ull * 1024ull;
   static_assert(NumberOfBytesIn2GB == 2147483648);
   if (fileSizeInBytes >= NumberOfBytesIn2GB)
   {
      return true;
   }
   return false;
}

// File Writes

void FileSystem::WriteTextFile(const fs::path& filePath, string_view fileText) const
{
   const fs::path parentFolderPath = filePath.parent_path();
   _call_fs_create_directories(parentFolderPath);
   FILE* const writeModeTextFilePointer = _fileOpenerCloser->CreateTextFileInWriteMode(filePath);
   const size_t fileTextSize = fileText.size();
   const size_t numberOfBytesWritten = _call_fwrite(fileText.data(), 1, fileTextSize, writeModeTextFilePointer);
   _asserter->ThrowIfSizeTsNotEqual(fileTextSize, numberOfBytesWritten,
      "fwrite() in FileSystem::CreateTextFile() unexpectedly did not return fileText.size() number of bytes written");
   _fileOpenerCloser->CloseFile(writeModeTextFilePointer);
}

// Misc

void FileSystem::DeleteFolder(const fs::path& folderPath) const
{
   _call_fs_remove_all(folderPath);
}

void FileSystem::SetCurrentPath(const fs::path& folderPath) const
{
   _call_fs_current_path(folderPath);
}

// Private Functions

size_t FileSystem::FileSize(FILE* filePointer) const
{
   const int fseekEndReturnValue = _call_fseek(filePointer, 0, SEEK_END);
   _asserter->ThrowIfIntsNotEqual(0, fseekEndReturnValue,
      "fseek(filePointer, 0, SEEK_END) in FileSystem::FileSize() unexpectedly did not return 0");
   const long ftellReturnValue = _call_ftell(filePointer);
   const int fseekSetReturnValue = _call_fseek(filePointer, 0, SEEK_SET);
   _asserter->ThrowIfIntsNotEqual(0, fseekSetReturnValue,
      "fseek(filePointer, 0, SEEK_SET) in FileSystem::FileSize() unexpectedly did not return 0");
   const size_t fileSizeInBytes = static_cast<size_t>(ftellReturnValue);
   return fileSizeInBytes;
}
