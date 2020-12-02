#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"

CloudundancyLogFileAppender::CloudundancyLogFileAppender()
   // Constant Components
   : _fileSystem(make_unique<FileSystem>())
   , _watch(make_unique<Watch>())
{
}


CloudundancyLogFileAppender::~CloudundancyLogFileAppender()
{
}

void CloudundancyLogFileAppender::AppendTextToCloudundancyLogFileInFolder(
   const fs::path& destinationFolderPath, string_view text) const
{
   const string dateTimeNow = _watch->DateTimeNow();
   const string timestampedBackupStartedMessage = String::Concat(dateTimeNow, '|', text, '\n');
   const fs::path cloudundancyLogFilePath = destinationFolderPath / "Cloudundancy.log";
   _fileSystem->AppendText(cloudundancyLogFilePath, timestampedBackupStartedMessage);
}
