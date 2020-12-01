#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"
#include "libCloudundancyTests/Components/Time/MetalMock/WatchMock.h"

TESTS(CloudundancyLogFileAppenderTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
EVIDENCE

CloudundancyLogFileAppender _cloudundancyLogFileAppender;
// Function Callers
using _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderMockType =
   OneExtraArgMemberFunctionForEacherMock<CloudundancyLogFileAppender, fs::path, string_view>;
_oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderMockType*
   _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderMock = nullptr;
// Constant Components
FileSystemMock* _fileSystemMock = nullptr;
WatchMock* _watchMock = nullptr;

STARTUP
{
   // Function Callers
   _cloudundancyLogFileAppender._oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolder.reset(
      _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderMock =
         new _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderMockType);
   // Constant Components
   _cloudundancyLogFileAppender._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _cloudundancyLogFileAppender._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyLogFileAppender cloudundancyLogFileAppender;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileAppender._oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolder);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileAppender._fileSystem);
}

TEST(AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders_CallsThrowIfFolderIsNotWritableOnEachDestinationFolderPath)
{
   _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderMock->CallConstMemberFunctionForEachElementMock.Expect();
   const vector<fs::path> destinationFolderPaths = ZenUnit::RandomVector<fs::path>();
   //
   _cloudundancyLogFileAppender.AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(destinationFolderPaths);
   //
   METALMOCK(_oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderMock->
      CallConstMemberFunctionForEachElementMock.CalledOnceWith(
         destinationFolderPaths,
         &CloudundancyLogFileAppender::AppendTextToCloudundancyLogFileInDestinationFolder,
         &_cloudundancyLogFileAppender, "Cloudundancy backup started"));
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
