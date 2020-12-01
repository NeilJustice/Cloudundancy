#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

TESTS(CloudundancyIniValidatorTests)
AFACT(DefaultConstructor_NewsFileSystem)
AFACT(ThrowIfZeroDestinationFolderPaths_DestinationFolderPathsIsEmpty_ThrowsFileSystemExceptionWithReasonMalformedFile)
EVIDENCE

CloudundancyIniValidator _cloudundancyIniValidator;
// Function Callers
using _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType =
   MemberFunctionForEacherMock<CloudundancyIniValidator, fs::path>;
_memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType*
   _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock = nullptr;
// Constant Components
FileSystemMock* _fileSystemMock = nullptr;

STARTUP
{
   _cloudundancyIniValidator._fileSystem.reset(_fileSystemMock = new FileSystemMock);
}

TEST(DefaultConstructor_NewsFileSystem)
{
   CloudundancyIniValidator cloudundancyIniValidator;
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

RUN_TESTS(CloudundancyIniValidatorTests)
