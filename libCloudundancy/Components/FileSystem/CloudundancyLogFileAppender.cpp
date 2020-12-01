#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"

CloudundancyLogFileAppender::CloudundancyLogFileAppender()
   // Function Callers
   : _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolder(
      make_unique<_oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderType>())
   // Constant Components
   , _fileSystem(make_unique<FileSystem>())
   , _watch(make_unique<Watch>())
{
}


CloudundancyLogFileAppender::~CloudundancyLogFileAppender()
{
}

// Confirms that all destination folders are writable
void CloudundancyLogFileAppender::AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(
   const vector<fs::path>& destinationFolderPaths) const
{
   _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolder->CallConstMemberFunctionForEachElement(
      destinationFolderPaths,
      &CloudundancyLogFileAppender::AppendTextToCloudundancyLogFileInDestinationFolder,
      this, "Cloudundancy backup started");
}

// Private Functions

void CloudundancyLogFileAppender::AppendTextToCloudundancyLogFileInDestinationFolder(
   const fs::path& destinationFolderPath, string_view text) const
{
   const string dateTimeNow = _watch->DateTimeNow();
   const string timestampedBackupStartedMessage = String::Concat(dateTimeNow, '|', text, '\n');
   const fs::path cloudundancyLogFilePath = destinationFolderPath / "Cloudundancy.log";
   _fileSystem->AppendText(cloudundancyLogFilePath, timestampedBackupStartedMessage);
}
