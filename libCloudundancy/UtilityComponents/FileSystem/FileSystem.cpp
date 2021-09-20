#include "pch.h"
#include "libCloudundancy/Exceptions/FileSystemExceptions.h"
#include "libCloudundancy/UtilityComponents/Assertion/Asserter.h"
#include "libCloudundancy/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FCloseDeleter.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FileSystem.h"
#include "libCloudundancy/UtilityComponents/FileSystem/PassthroughFileSystem.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/NonVoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/UtilityComponents/Memory/CharVectorAllocator.h"
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"
#include "libCloudundancy/UtilityComponents/Time/StopwatchFactory.h"

namespace Utils
{
   FileSystem::FileSystem()
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
      , _call_fs_copy_file(static_cast<fs_copy_file_FunctionOverloadType>(fs::copy_file))
      , _call_fs_create_directories(static_cast<fs_create_directories_FunctionOverloadType>(fs::create_directories))
      , _call_fs_current_path(static_cast<fs_current_path_FunctionOverloadType>(fs::current_path))
      , _call_fs_exists(static_cast<fs_exists_FunctionOverloadType>(fs::exists))
      // Function Callers
      , _caller_CreateOrOpenFileFunction(make_unique<_caller_CreateOrOpenFileFunctionType>())
      , _caller_ReadFileBytes(make_unique<_caller_ReadFileBytesType>())
      , _caller_ReadFileSize(make_unique<_caller_ReadFileSizeType>())
      , _caller_ReadFileText(make_unique<_caller_ReadFileTextType>())
      , _caller_WriteTextToOpenFile(make_unique<_caller_WriteTextToOpenFileType>())
#if defined __linux__
      , _caller_CreateOrOpenFileOnLinux(make_unique<_caller_CreateOrOpenFileOnLinuxType>())
#elif defined _WIN32
      , _caller_CreateOrOpenFileOnWindows(make_unique<_caller_CreateOrOpenFileOnWindowsType>())
#endif
      // Constant Components
      , _asserter(make_unique<Asserter>())
      , _charVectorAllocator(make_unique<CharVectorAllocator>())
      , _errorCodeTranslator(make_unique<ErrorCodeTranslator>())
      , _passthroughFileSystem(make_unique<PassthroughFileSystem>())
      , _stopwatchFactory(make_unique<StopwatchFactory>())
   {
   }

   FileSystem::~FileSystem()
   {
   }

   // File Open Functions

   shared_ptr<FILE> FileSystem::CreateFileInBinaryWriteMode(const fs::path& filePath) const
   {
#if defined __linux__
      shared_ptr<FILE> binaryWriteModeFilePointer =
         _caller_CreateOrOpenFileOnLinux->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnLinux, this, filePath, "wb");
#elif defined _WIN32
      shared_ptr<FILE> binaryWriteModeFilePointer =
         _caller_CreateOrOpenFileOnWindows->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnWindows, this, filePath, L"wb");
#endif
      return binaryWriteModeFilePointer;
   }

   shared_ptr<FILE> FileSystem::CreateOrOpenFileInBinaryAppendMode(const fs::path& filePath) const
   {
#if defined __linux__
      shared_ptr<FILE> binaryAppendModeFilePointer =
         _caller_CreateOrOpenFileOnLinux->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnLinux, this, filePath, "ab");
#elif defined _WIN32
      shared_ptr<FILE> binaryAppendModeFilePointer =
         _caller_CreateOrOpenFileOnWindows->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnWindows, this, filePath, L"ab");
#endif
      return binaryAppendModeFilePointer;
   }

   void FileSystem::DeleteFolder(const fs::path& folderPath) const
   {
      _passthroughFileSystem->remove_all(folderPath);
   }

   shared_ptr<FILE> FileSystem::OpenFileInBinaryReadMode(const fs::path& filePath) const
   {
#if defined __linux__
      shared_ptr<FILE> binaryReadModeFilePointer =
         _caller_CreateOrOpenFileOnLinux->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnLinux, this, filePath, "rb");
#elif defined _WIN32
      shared_ptr<FILE> binaryReadModeFilePointer =
         _caller_CreateOrOpenFileOnWindows->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnWindows, this, filePath, L"rb");
#endif
      return binaryReadModeFilePointer;
   }

   shared_ptr<FILE> FileSystem::OpenFileInTextReadMode(const fs::path& filePath) const
   {
   #if defined __linux__
      shared_ptr<FILE> textReadModeFilePointer =
         _caller_CreateOrOpenFileOnLinux->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnLinux, this, filePath, "r");
   #elif defined _WIN32
      shared_ptr<FILE> textReadModeFilePointer =
         _caller_CreateOrOpenFileOnWindows->CallConstMemberFunction(&FileSystem::CreateOrOpenFileOnWindows, this, filePath, L"r");
   #endif
      return textReadModeFilePointer;
   }

   // Behavior Functions

   void FileSystem::AppendTextToClosedFile(const fs::path& filePath, string_view text) const
   {
      const shared_ptr<FILE> appendModeBinaryFilePointer =
         _caller_CreateOrOpenFileFunction->CallConstMemberFunction(&FileSystem::CreateOrOpenFileInBinaryAppendMode, this, filePath);
      const size_t textSize = text.size();
      const size_t numberOfBytesAppended = _call_fwrite(text.data(), 1, textSize, appendModeBinaryFilePointer.get());
      _asserter->ThrowIfSizeTsNotEqual(textSize, numberOfBytesAppended,
         "_call_fwrite(text.data(), 1, textSize, appendModeTextFileHandle) unexpectedly did not return textSize");
   }

   void FileSystem::CloseFile(const shared_ptr<FILE>& filePointer, const fs::path& filePath) const
   {
      const int fcloseReturnValue = _call_fclose(filePointer.get());
      if (fcloseReturnValue != 0)
      {
         const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
         const string exceptionMessage = Utils::String::ConcatValues(
            "fclose(filePointer) when closing file ", filePath.string(), " returned ", errnoWithDescription.first, ": ", errnoWithDescription.second);
         throw runtime_error(exceptionMessage);
      }
   }

   Utils::FileCopyResult FileSystem::CopyFileToFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
   {
      const shared_ptr<Stopwatch> stopwatch = _stopwatchFactory->NewStopwatch();
      stopwatch->Start();
      shared_ptr<const vector<char>> sourceFileBytes = _caller_ReadFileBytes->CallConstMemberFunction(&FileSystem::ReadFileBytes, this, sourceFilePath);
      const fs::path parentPathOfDestinationFilePath = destinationFilePath.parent_path();
      _call_fs_create_directories(parentPathOfDestinationFilePath);
      const shared_ptr<FILE> binaryWriteModeDestinationFilePointer =
         _caller_CreateOrOpenFileFunction->CallConstMemberFunction(&FileSystem::CreateFileInBinaryWriteMode, this, destinationFilePath);
      const size_t sourceFileSize = sourceFileBytes->size();
      size_t numberOfBytesWritten = 0;
      if (sourceFileSize > 0)
      {
         numberOfBytesWritten = _call_fwrite(sourceFileBytes->data(), 1, sourceFileSize, binaryWriteModeDestinationFilePointer.get());
      }
      _asserter->ThrowIfSizeTsNotEqual(sourceFileSize, numberOfBytesWritten,
         "fwrite() in Utils::FileSystem::CopyFileToFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) unexpectedly returned numberOfBytesWritten != sourceFileSize");
      Utils::FileCopyResult successFileCopyResult;
      successFileCopyResult.sourceFilePath = sourceFilePath;
      successFileCopyResult.destinationFilePath = destinationFilePath;
      successFileCopyResult.copySucceeded = true;
      successFileCopyResult.durationInMilliseconds = stopwatch->StopAndGetElapsedMilliseconds();
      return successFileCopyResult;
   }

   Utils::FileCopyResult FileSystem::CopyFileToFileLargerThan2GB(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
   {
      const shared_ptr<Stopwatch> stopwatch = _stopwatchFactory->NewStopwatch();
      stopwatch->Start();
      const fs::path parentFolderPathForDestinationFile = destinationFilePath.parent_path();
      _call_fs_create_directories(parentFolderPathForDestinationFile);
      Utils::FileCopyResult fileCopyResult;
      fileCopyResult.sourceFilePath = sourceFilePath;
      fileCopyResult.destinationFilePath = destinationFilePath;
      fileCopyResult.copySucceeded = _call_fs_copy_file(sourceFilePath, destinationFilePath, fs::copy_options::overwrite_existing);
      fileCopyResult.durationInMilliseconds = stopwatch->StopAndGetElapsedMilliseconds();
      return fileCopyResult;
   }

   void FileSystem::CreateFileWithTextIfDoesNotExist(const fs::path& filePath, string_view fileText) const
   {
      const bool fileExists = _call_fs_exists(filePath);
      if (!fileExists)
      {
         const shared_ptr<FILE> binaryWriteModeFilePointer =
            _caller_CreateOrOpenFileFunction->CallConstMemberFunction(&FileSystem::CreateFileInBinaryWriteMode, this, filePath);
         _caller_WriteTextToOpenFile->CallConstMemberFunction(&FileSystem::WriteTextToOpenFile, this, binaryWriteModeFilePointer, fileText);
      }
   }

   bool FileSystem::FileOrFolderExists(const fs::path& fileOrFolderPath) const
   {
      const bool fileOrFolderExists = _call_fs_exists(fileOrFolderPath);
      return fileOrFolderExists;
   }

   shared_ptr<const vector<char>> FileSystem::ReadFileBytes(const fs::path& filePath) const
   {
      const shared_ptr<FILE> binaryReadModeFilePointer =
         _caller_CreateOrOpenFileFunction->CallConstMemberFunction(&FileSystem::OpenFileInBinaryReadMode, this, filePath);
      const size_t fileSize = _caller_ReadFileSize->CallConstMemberFunction(&FileSystem::ReadFileSize, this, binaryReadModeFilePointer);
      if (fileSize == 0)
      {
         shared_ptr<const vector<char>> emptyFileBytes = make_shared<vector<char>>(vector<char>{});
         return emptyFileBytes;
      }
      const unique_ptr<vector<char>> fileBytesBuffer(_charVectorAllocator->NewCharVector(fileSize));
      const size_t numberOfBytesRead = _call_fread(&(*fileBytesBuffer)[0], 1, fileSize, binaryReadModeFilePointer.get());
      _asserter->ThrowIfSizeTsNotEqual(fileSize, numberOfBytesRead,
         "fread() in Utils::FileSystem::ReadFileBytes(const fs::path& filePath) unexpectedly did not return fileSize");
      shared_ptr<const vector<char>> fileBytes = make_shared<vector<char>>(*fileBytesBuffer);
      return fileBytes;
   }

   vector<string> FileSystem::ReadFileLinesWhichMustBeNonEmpty(const fs::path& filePath) const
   {
      const string fileText = _caller_ReadFileText->CallConstMemberFunction(&FileSystem::ReadFileText, this, filePath);
      if (fileText.empty())
      {
         throw FileMalformedException(filePath, "File cannot be empty");
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

   string FileSystem::ReadFileText(const fs::path& filePath) const
   {
      const shared_ptr<FILE> textReadModeFilePointer =
         _caller_CreateOrOpenFileFunction->CallConstMemberFunction(&FileSystem::OpenFileInTextReadMode, this, filePath);
      const size_t fileSize = _caller_ReadFileSize->CallConstMemberFunction(&FileSystem::ReadFileSize, this, textReadModeFilePointer);
      vector<char> fileBytesBuffer(fileSize, 0);
      size_t numberOfTextModeBytesRead = 0;
      if (fileSize > 0)
      {
         numberOfTextModeBytesRead = _call_fread(fileBytesBuffer.data(), 1, fileSize, textReadModeFilePointer.get());
      }
      string fileText(fileBytesBuffer.data(), numberOfTextModeBytesRead);
      return fileText;
   }

   void FileSystem::SetCurrentPath(const fs::path& folderPath) const
   {
      _call_fs_current_path(folderPath);
   }

   void FileSystem::ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist(const fs::path& filePath) const
   {
      if (!filePath.empty())
      {
         const bool filePathExists = _call_fs_exists(filePath);
         if (!filePathExists)
         {
            throw FileNotFoundException(filePath);
         }
      }
   }

   void FileSystem::WriteTextToOpenFile(const shared_ptr<FILE>& filePointer, string_view text) const
   {
      const size_t textSize = text.size();
      const size_t numberOfBytesWritten = _call_fwrite(text.data(), 1, textSize, filePointer.get());
      _asserter->ThrowIfSizeTsNotEqual(textSize, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != textSize");
      const int flushReturnValue = _call_fflush(filePointer.get());
      _asserter->ThrowIfIntsNotEqual(0, flushReturnValue, "fflush() unexpectedly did not return 0");
   }

   void FileSystem::WriteBytesToOpenFile(const shared_ptr<FILE>& filePointer, const void* bytes, size_t bytesLength) const
   {
      const size_t numberOfBytesWritten = _call_fwrite(bytes, 1, bytesLength, filePointer.get());
      _asserter->ThrowIfSizeTsNotEqual(bytesLength, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != bytesLength");
      const int flushReturnValue = _call_fflush(filePointer.get());
      _asserter->ThrowIfIntsNotEqual(0, flushReturnValue, "fflush() unexpectedly did not return 0");
   }

   // Private Functions

#if defined __linux__

   shared_ptr<FILE> FileSystem::CreateOrOpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const
   {
      const fs::path parentDirectoryPath = filePath.parent_path();
      _call_fs_create_directories(parentDirectoryPath);
      FILE* const rawFilePointer = _call_fopen(filePath.c_str(), fileOpenMode);
      if (rawFilePointer == nullptr)
      {
         const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
         const string exceptionMessage = Utils::String::ConcatValues(
            "fopen(filePath.c_str(), fileOpenMode) returned nullptr. ",
            "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
         throw runtime_error(exceptionMessage);
      }
      shared_ptr<FILE> filePointer(rawFilePointer, FCloseDeleter());
      return filePointer;
   }

#elif defined _WIN32

   shared_ptr<FILE> FileSystem::CreateOrOpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const
   {
      const fs::path parentDirectoryPath = filePath.parent_path();
      _call_fs_create_directories(parentDirectoryPath);
      FILE* const rawFilePointer = _call_wfsopen(filePath.c_str(), fileOpenMode, _SH_DENYWR);
      if (rawFilePointer == nullptr)
      {
         const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
         const string exceptionMessage = Utils::String::ConcatValues(
            "_wfsopen(filePath.c_str(), fileOpenMode, _SH_DENYWR) returned nullptr. ",
            "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
         throw runtime_error(exceptionMessage);
      }
      shared_ptr<FILE> filePointer(rawFilePointer, FCloseDeleter());
      return filePointer;
   }

#endif

   size_t FileSystem::ReadFileSize(const shared_ptr<FILE>& filePointer) const
   {
      const int fseekEndReturnValue = _call_fseek(filePointer.get(), 0, SEEK_END);
      _asserter->ThrowIfIntsNotEqual(0, fseekEndReturnValue, "fseek(filePointer.get(), 0, SEEK_END) in FileSystem::FileSize() unexpectedly did not return 0");
      const long ftellReturnValue = _call_ftell(filePointer.get());
      const int fseekSetReturnValue = _call_fseek(filePointer.get(), 0, SEEK_SET);
      _asserter->ThrowIfIntsNotEqual(0, fseekSetReturnValue, "fseek(filePointer.get(), 0, SEEK_SET) in FileSystem::FileSize() unexpectedly did not return 0");
      const size_t fileSizeInBytes = static_cast<size_t>(ftellReturnValue);
      return fileSizeInBytes;
   }
}
