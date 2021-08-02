#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/RawFileSystemMock.h"

TESTS(CloudundancyLogFileWriterTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
EVIDENCE

CloudundancyLogFileWriter _cloudundancyLogFileWriter;
// Constant Components
Utils::RawFileSystemMock* _rawFileSystemMock = nullptr;
Utils::WatchMock* _watchMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyLogFileWriter._rawFileSystem.reset(_rawFileSystemMock = new Utils::RawFileSystemMock);
   _cloudundancyLogFileWriter._watch.reset(_watchMock = new Utils::WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyLogFileWriter cloudundancyLogFileWriter;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileWriter._rawFileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyLogFileWriter._watch);
}

TEST(AppendTimestampedTextToCloudundancyLogFileInDestinationFolder_AppendsTimestampedTextToCloudundancyDotLogInDestinationFolder)
{
   const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
   _rawFileSystemMock->AppendTextToClosedFileMock.Expect();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _cloudundancyLogFileWriter.AppendTextToCloudundancyLogFileInFolder(folderPath, text);
   //
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   const fs::path expectedCloudundancyLogFilePath = folderPath / "Cloudundancy.log";
   const string expectedTimestampedBackupStartedMessage = Utils::String::ConcatStrings(dateTimeNow, "|", text, "\n");
   METALMOCK(_rawFileSystemMock->AppendTextToClosedFileMock.CalledOnceWith(expectedCloudundancyLogFilePath, expectedTimestampedBackupStartedMessage));
}

RUN_TESTS(CloudundancyLogFileWriterTests)
