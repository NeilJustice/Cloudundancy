#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"

TESTS(CloudundancyLogFileWriterTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
EVIDENCE

CloudundancyLogFileWriter _cloudundancyLogFileWriter;
// Constant Components
FileSystemMock* _fileSystemMock = nullptr;
WatchMock* _watchMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyLogFileWriter._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _cloudundancyLogFileWriter._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyLogFileWriter cloudundancyLogFileWriter;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileWriter._fileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileWriter._watch);
}

TEST(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
{
   const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
   _fileSystemMock->AppendTextMock.Expect();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _cloudundancyLogFileWriter.AppendTextToCloudundancyLogFileInFolder(folderPath, text);
   //
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   const fs::path expectedCloudundancyLogFilePath = folderPath / "Cloudundancy.log";
   const string expectedTimestampedBackupStartedMessage = String::ConcatStrings(dateTimeNow, "|", text, "\n");
   METALMOCK(_fileSystemMock->AppendTextMock.CalledOnceWith(
      expectedCloudundancyLogFilePath, expectedTimestampedBackupStartedMessage));
}

RUN_TESTS(CloudundancyLogFileWriterTests)
