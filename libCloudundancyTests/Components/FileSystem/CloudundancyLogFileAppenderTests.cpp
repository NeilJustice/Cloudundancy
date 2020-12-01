#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"
#include "libCloudundancyTests/Components/Time/MetalMock/WatchMock.h"

TESTS(CloudundancyLogFileAppenderTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders_CallsThrowIfFolderIsNotWritableOnEachDestinationFolderPath)
AFACT(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
EVIDENCE

CloudundancyLogFileAppender _cloudundancyLogFileAppender;
// Function Callers
using _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType =
MemberFunctionForEacherMock<CloudundancyLogFileAppender, fs::path>;
_memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType*
   _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock = nullptr;
// Constant Components
FileSystemMock* _fileSystemMock = nullptr;
WatchMock* _watchMock = nullptr;

STARTUP
{
   // Function Callers
   _cloudundancyLogFileAppender._memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder.reset(
      _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock =
         new _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMockType);
   // Constant Components
   _cloudundancyLogFileAppender._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _cloudundancyLogFileAppender._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyLogFileAppender cloudundancyLogFileAppender;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileAppender._memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileAppender._fileSystem);
}

TEST(AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders_CallsThrowIfFolderIsNotWritableOnEachDestinationFolderPath)
{
   _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock->
      CallConstMemberFunctionForEachElementMock.Expect();
   const vector<fs::path> destinationFolderPaths = ZenUnit::RandomVector<fs::path>();
   //
   _cloudundancyLogFileAppender.AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(destinationFolderPaths);
   //
   METALMOCK(_memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderMock->
      CallConstMemberFunctionForEachElementMock.CalledOnceWith(
         destinationFolderPaths, &CloudundancyLogFileAppender::AppendBackupStartedToCloudundancyLogFileInDestinationFolder, &_cloudundancyLogFileAppender));
}

TEST(AppendBackupStartedToCloudundancyLogFileInDestinationFolder_AppendsTimestampedCloudundancyBackupStartedMessageToCloudundancyDotLogInDestinationFolder)
{
   const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
   _fileSystemMock->AppendTextMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyLogFileAppender.AppendBackupStartedToCloudundancyLogFileInDestinationFolder(destinationFolderPath);
   //
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   const fs::path expectedCloudundancyLogFilePath = destinationFolderPath / "Cloudundancy.log";
   const string expectedTimestampedBackupStartedMessage = dateTimeNow + " Cloudundancy backup started\n";
   METALMOCK(_fileSystemMock->AppendTextMock.CalledOnceWith(
      expectedCloudundancyLogFilePath, expectedTimestampedBackupStartedMessage));
}

TEST(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
{
   const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
   _fileSystemMock->AppendTextMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _cloudundancyLogFileAppender.AppendTextToCloudundancyLogFileInDestinationFolder(destinationFolderPath, text);
   //
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   const fs::path expectedCloudundancyLogFilePath = destinationFolderPath / "Cloudundancy.log";
   const string expectedTimestampedBackupStartedMessage = String::Concat(dateTimeNow, '|', text, '\n');
   METALMOCK(_fileSystemMock->AppendTextMock.CalledOnceWith(
      expectedCloudundancyLogFilePath, expectedTimestampedBackupStartedMessage));
}

RUN_TESTS(CloudundancyLogFileAppenderTests)
