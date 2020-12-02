#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/WatchMock.h"

TESTS(CloudundancyLogFileAppenderTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
EVIDENCE

CloudundancyLogFileAppender _cloudundancyLogFileAppender;
// Constant Components
FileSystemMock* _fileSystemMock = nullptr;
WatchMock* _watchMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyLogFileAppender._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _cloudundancyLogFileAppender._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyLogFileAppender cloudundancyLogFileAppender;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileAppender._fileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileAppender._watch);
}

TEST(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
{
   const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
   _fileSystemMock->AppendTextMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _cloudundancyLogFileAppender.AppendTextToCloudundancyLogFileInFolder(destinationFolderPath, text);
   //
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   const fs::path expectedCloudundancyLogFilePath = destinationFolderPath / "Cloudundancy.log";
   const string expectedTimestampedBackupStartedMessage = String::Concat(dateTimeNow, '|', text, '\n');
   METALMOCK(_fileSystemMock->AppendTextMock.CalledOnceWith(
      expectedCloudundancyLogFilePath, expectedTimestampedBackupStartedMessage));
}

RUN_TESTS(CloudundancyLogFileAppenderTests)
