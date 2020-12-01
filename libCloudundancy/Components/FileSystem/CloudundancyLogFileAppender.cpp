#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"
#include "libCloudundancy/Components/Iteration/ForEach/MemberFunctionForEacher.h"
#include "libCloudundancy/Components/Time/Watch.h"

CloudundancyLogFileAppender::CloudundancyLogFileAppender()
   // Function Callers
   : _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder(
      make_unique<_memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType>())
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
   _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder->CallConstMemberFunctionForEachElement(
      destinationFolderPaths, &CloudundancyLogFileAppender::AppendBackupStartedToCloudundancyLogFileInDestinationFolder, this);
}

// Private Functions

void CloudundancyLogFileAppender::AppendBackupStartedToCloudundancyLogFileInDestinationFolder(
   const fs::path& destinationFolderPath) const
{
   const string dateTimeNow = _watch->DateTimeNow();
   const string timestampedBackupStartedMessage = dateTimeNow + " Cloudundancy backup started\n";
   const fs::path cloudundancyLogFilePath = destinationFolderPath / "Cloudundancy.log";
   _fileSystem->AppendText(cloudundancyLogFilePath, timestampedBackupStartedMessage);
}
