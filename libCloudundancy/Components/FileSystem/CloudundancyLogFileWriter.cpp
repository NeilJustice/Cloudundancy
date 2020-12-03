#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"

CloudundancyLogFileWriter::CloudundancyLogFileWriter()
   // Constant Components
   : _fileSystem(make_unique<FileSystem>())
   , _watch(make_unique<Watch>())
{
}


CloudundancyLogFileWriter::~CloudundancyLogFileWriter()
{
}

void CloudundancyLogFileWriter::AppendTextToCloudundancyLogFileInFolder(const fs::path& folderPath, string_view text) const
{
   const string dateTimeNow = _watch->DateTimeNow();
   const string timestampedBackupStartedMessage = String::Concat(dateTimeNow, '|', text, '\n');
   const fs::path cloudundancyLogFilePath = folderPath / "Cloudundancy.log";
   _fileSystem->AppendText(cloudundancyLogFilePath, timestampedBackupStartedMessage);
}
