#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

TESTS(CloudundancyIniValidatorTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(ThrowIfZeroDestinationFolderPaths_DestinationFolderPathsIsEmpty_ThrowsFileSystemExceptionWithReasonMalformedFile)
AFACT(AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders_CallsThrowIfFolderIsNotWritableOnEachDestinationFolderPath)
EVIDENCE

CloudundancyIniValidator _cloudundancyIniValidator;
// Function Callers
using _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType =
   OneExtraArgMemberFunctionForEacherMock<CloudundancyIniValidator, fs::path, fs::path>;
_memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType*
   _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock = nullptr;
// Constant Components
FileSystemMock* _fileSystemMock = nullptr;

STARTUP
{
   // Function Callers
   _cloudundancyIniValidator._memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder.reset(
      _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock =
         new _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType);
   // Constant Components
   _cloudundancyIniValidator._fileSystem.reset(_fileSystemMock = new FileSystemMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyIniValidator cloudundancyIniValidator;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyIniValidator._memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyIniValidator._fileSystem);
}

TEST(ThrowIfZeroDestinationFolderPaths_DestinationFolderPathsIsEmpty_ThrowsFileSystemExceptionWithReasonMalformedFile)
{
   CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   cloudundancyIni.destinationFolderPaths = {};
   //
   const fs::path cloudundancyIniPath = ZenUnit::Random<fs::path>();
   const FileSystemException expectedFileSystemException(
      FileSystemExceptionType::MalformedFile, cloudundancyIniPath, "cloudundancyIni.destinationFolderPaths cannot be empty");
   const string expectedExceptionMessage = expectedFileSystemException.what();
   THROWS_EXCEPTION(_cloudundancyIniValidator.ThrowIfZeroDestinationFolderPaths(cloudundancyIni, cloudundancyIniPath),
      FileSystemException, expectedExceptionMessage);
}

TEST(AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders_CallsThrowIfFolderIsNotWritableOnEachDestinationFolderPath)
{
   _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock->
      CallConstMemberFunctionForEachElementMock.Expect();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const fs::path cloudundancyIniPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyIniValidator.AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(cloudundancyIni, cloudundancyIniPath);
   //
   METALMOCK(_memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock->
      CallConstMemberFunctionForEachElementMock.CalledOnceWith(
         cloudundancyIni.destinationFolderPaths,
         &CloudundancyIniValidator::AppendBackupStartedToCloudundancyLogFileInDestinationFolder,
         &_cloudundancyIniValidator, cloudundancyIniPath));
}

RUN_TESTS(CloudundancyIniValidatorTests)
