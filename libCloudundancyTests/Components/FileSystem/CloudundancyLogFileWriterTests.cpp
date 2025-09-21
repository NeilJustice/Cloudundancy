#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/FileSystemMock.h"

TESTS(CloudundancyLogFileWriterTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
EVIDENCE

CloudundancyLogFileWriter _cloudundancyLogFileWriter;
// Constant Components
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::WatchMock* _watchMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyLogFileWriter._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _cloudundancyLogFileWriter._watch.reset(_watchMock = new Utils::WatchMock);
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
   _fileSystemMock->AppendTextToClosedFileMock.Expect();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _cloudundancyLogFileWriter.AppendTextToCloudundancyLogFileInFolder(folderPath, text);
   //
   const fs::path expectedCloudundancyLogFilePath = folderPath / "Cloudundancy.log";
   const string expectedTimestampedBackupStartedMessage = Utils::String::ConcatStrings(dateTimeNow, "|", text, "\n");
   METALMOCKTHEN(_watchMock->DateTimeNowMock.CalledOnce()).Then(
   METALMOCKTHEN(_fileSystemMock->AppendTextToClosedFileMock.CalledOnceWith(
      expectedCloudundancyLogFilePath, expectedTimestampedBackupStartedMessage)));
}

RUN_TESTS(CloudundancyLogFileWriterTests)
