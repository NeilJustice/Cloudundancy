#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FileSystem.h"

CloudundancyLogFileWriter::CloudundancyLogFileWriter()
   // Constant Components
   : _fileSystem(make_unique<Utils::FileSystem>())
   , _watch(make_unique<Utils::Watch>())
{
}

CloudundancyLogFileWriter::~CloudundancyLogFileWriter()
{
}

void CloudundancyLogFileWriter::AppendTextToCloudundancyLogFileInFolder(const fs::path& folderPath, string_view text) const
{
   const string dateTimeNow = _watch->DateTimeNow();
   const string timestampedBackupStartedMessage = Utils::String::ConcatStrings(dateTimeNow, "|", text, "\n");
   const fs::path cloudundancyLogFilePath = folderPath / "Cloudundancy.log";
   _fileSystem->AppendTextToClosedFile(cloudundancyLogFilePath, timestampedBackupStartedMessage);
}
