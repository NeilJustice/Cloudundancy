#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"
#include "libCloudundancy/Components/Iteration/ForEach/MemberFunctionForEacher.h"
#include "libCloudundancy/Components/Time/Watch.h"

CloudundancyIniValidator::CloudundancyIniValidator()
   // Function Callers
   : _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder(
      make_unique<_memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType>())
   // Constant Components
   , _fileSystem(make_unique<FileSystem>())
   , _watch(make_unique<Watch>())
{
}

CloudundancyIniValidator::~CloudundancyIniValidator()
{
}

void CloudundancyIniValidator::ThrowIfZeroDestinationFolderPaths(
   const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const
{
   if (cloudundancyIni.destinationFolderPaths.empty())
   {
      const FileSystemException fileSystemException(
         FileSystemExceptionType::MalformedFile, cloudundancyIniPath, "cloudundancyIni.destinationFolderPaths cannot be empty");
      throw fileSystemException;
   }
}

// Confirms that all destination folders are writable
void CloudundancyIniValidator::AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(
   const CloudundancyIni& cloudundancyIni) const
{
   _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder->CallConstMemberFunctionForEachElement(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyIniValidator::AppendBackupStartedToCloudundancyLogFileInDestinationFolder, this);
}

// Private Functions

void CloudundancyIniValidator::AppendBackupStartedToCloudundancyLogFileInDestinationFolder(
   const fs::path& destinationFolderPath) const
{
   const string dateTimeNow = _watch->DateTimeNow();
   const string timestampedBackupStartedMessage = dateTimeNow + " Cloudundancy backup started\n";
   const fs::path cloudundancyLogFilePath = destinationFolderPath / "Cloudundancy.log";
   _fileSystem->AppendText(cloudundancyLogFilePath, timestampedBackupStartedMessage);
}
