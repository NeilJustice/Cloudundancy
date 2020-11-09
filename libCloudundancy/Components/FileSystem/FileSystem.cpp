#include "pch.h"
#include "libCloudundancy/Components/Assertion/Asserter.h"
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/FileSystem/FileSystemException.h"
#include "libCloudundancy/Components/Memory/CharVectorAllocator.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/FunctionCallers/Member/NonVoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/StaticUtilities/Errno.h"

#ifdef __linux__
int* GetLinuxErrno()
{
   return &errno;
}
#endif

FileSystem::FileSystem()
   // Constant Components
   : _asserter(make_unique<Asserter>())
   , _charVectorAllocator(make_unique<CharVectorAllocator>())
   , _fileOpenerCloser(make_unique<FileOpenerCloser>())
   // Function Pointers
#ifdef __linux__
   , _call_errno(GetLinuxErrno)
#elif _WIN32
   , _call_errno(::_errno)
#endif
   , _call_fread(::fread)
   , _call_fseek(::fseek)
   , _call_fs_current_path(static_cast<void(*)(const fs::path&)>(fs::current_path))
   , _call_fs_create_directories_as_assignable_function_overload_pointer(fs::create_directories)
   , _call_fwrite(::fwrite)
   , _call_ftell(::ftell)
   , _call_std_filesystem_remove_all(static_cast<uintmax_t(*)(const fs::path&)>(fs::remove_all))
   , _call_std_filesystem_exists_as_assignable_function_overload_pointer(fs::exists)
   // Function Callers
   , _caller_ReadAsciiFileText(make_unique< _caller_ReadAsciiFileText_Type>())
   , _caller_ReadFileBytes(make_unique<_caller_ReadFileBytes_Type>())
   , _caller_ReadFileSize(make_unique<_caller_ReadFileSize_Type>())
   // Mutable Components
   , _stopwatch(make_unique<Stopwatch>())
{
   _call_fs_create_directories = _call_fs_create_directories_as_assignable_function_overload_pointer;
   _call_std_filesystem_exists = _call_std_filesystem_exists_as_assignable_function_overload_pointer;
}

FileSystem::~FileSystem()
{
}

void FileSystem::DeleteFolder(const fs::path& folderPath) const
{
   _call_std_filesystem_remove_all(folderPath);
}

bool FileSystem::FileOrFolderExists(const fs::path& fileOrFolderPath) const
{
   const bool fileOrFolderExists = _call_std_filesystem_exists(fileOrFolderPath);
   return fileOrFolderExists;
}

vector<char> FileSystem::ReadFileBytes(const fs::path& filePath) const
{
   FILE* const readModeBinaryFilePointer = _fileOpenerCloser->OpenBinaryFileInReadMode(filePath);
   const size_t fileSizeInBytes = _caller_ReadFileSize->CallConstMemberFunction(
      &FileSystem::ReadFileSize, this, readModeBinaryFilePointer);
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

vector<string> FileSystem::ReadAsciiFileLinesWhichMustBeNonEmpty(const fs::path& filePath) const
{
   const string fileText = _caller_ReadAsciiFileText->CallConstMemberFunction(&FileSystem::ReadAsciiFileText, this, filePath);
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

string FileSystem::ReadAsciiFileText(const fs::path& filePath) const
{
   FILE* const readModeTextFilePointer = _fileOpenerCloser->OpenTextFileInReadMode(filePath);
   const size_t fileSizeInBytes = _caller_ReadFileSize->CallConstMemberFunction(
      &FileSystem::ReadFileSize, this, readModeTextFilePointer);
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

void FileSystem::SetCurrentPath(const fs::path& folderPath) const
{
   _call_fs_current_path(folderPath);
}

void FileSystem::ThrowIfFilePathIsNotEmptyAndDoesNotExist(const fs::path& filePath) const
{
   if (!filePath.empty())
   {
      const bool filePathExists = _call_std_filesystem_exists(filePath);
      if (!filePathExists)
      {
         throw FileSystemException(FileSystemExceptionType::FileDoesNotExist, filePath);
      }
   }
}

FileCopyResult FileSystem::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
{
   _stopwatch->Start();
   vector<char> readFileBytesReturnValue =
      _caller_ReadFileBytes->CallConstMemberFunction(&FileSystem::ReadFileBytes, this, sourceFilePath);
   if (readFileBytesReturnValue.empty())
   {
      FileCopyResult emptyFileNotCopiedResult;
      emptyFileNotCopiedResult.sourceFilePath = sourceFilePath;
      emptyFileNotCopiedResult.destinationFilePath = destinationFilePath;
      emptyFileNotCopiedResult.errorMessage = "empty file";
      return emptyFileNotCopiedResult;
   }
   try
   {
      const fs::path parentPathOfDestinationFilePath = destinationFilePath.parent_path();
      _call_fs_create_directories(parentPathOfDestinationFilePath);
   }
   catch (const fs::filesystem_error& ex)
   {
      FileCopyResult failedFileCopyResult;
      failedFileCopyResult.sourceFilePath = sourceFilePath;
      failedFileCopyResult.destinationFilePath = destinationFilePath;
      failedFileCopyResult.copySucceeded = false;
      const char* const errorMessage = ex.what();
      failedFileCopyResult.errorMessage = errorMessage;
      failedFileCopyResult.durationInMilliseconds = _stopwatch->StopAndGetElapsedMilliseconds();
      return failedFileCopyResult;
   }
   _sourceFileBytes = std::move(readFileBytesReturnValue);
   FILE* const writeModeDestinationBinaryFilePointer = _fileOpenerCloser->CreateBinaryFileInWriteMode(destinationFilePath);
   const size_t sourceFileSizeInBytes = _sourceFileBytes.size();
   const size_t numberOfBytesWritten = _call_fwrite(
      &_sourceFileBytes[0], 1, sourceFileSizeInBytes, writeModeDestinationBinaryFilePointer);
   _asserter->ThrowIfSizeTsNotEqual(sourceFileSizeInBytes, numberOfBytesWritten,
      "fwrite() in FileSystem::TryCopyFile() unexpectedly returned numberOfBytesWritten != sourceFileSizeInBytes");
   _fileOpenerCloser->CloseFile(writeModeDestinationBinaryFilePointer);
   FileCopyResult successFileCopyResult;
   successFileCopyResult.sourceFilePath = sourceFilePath;
   successFileCopyResult.destinationFilePath = destinationFilePath;
   successFileCopyResult.copySucceeded = true;
   successFileCopyResult.durationInMilliseconds = _stopwatch->StopAndGetElapsedMilliseconds();
   return successFileCopyResult;
}

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

// Private Functions

size_t FileSystem::ReadFileSize(FILE* filePointer) const
{
   const int fseekEndReturnValue = _call_fseek(filePointer, 0, SEEK_END);
   _asserter->ThrowIfIntsNotEqual(0, fseekEndReturnValue,
      "fseek(filePointer, 0, SEEK_END) in FileSystem::ReadFileSize() unexpectedly did not return 0");
   const long ftellReturnValue = _call_ftell(filePointer);
   const int fseekSetReturnValue = _call_fseek(filePointer, 0, SEEK_SET);
   _asserter->ThrowIfIntsNotEqual(0, fseekSetReturnValue,
      "fseek(filePointer, 0, SEEK_SET) in FileSystem::ReadFileSize() unexpectedly did not return 0");
   const size_t fileSizeInBytes = static_cast<size_t>(ftellReturnValue);
   return fileSizeInBytes;
}
