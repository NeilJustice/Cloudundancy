#pragma once
struct CloudundancyIni;
template<typename ClassType, typename ElementType>
class MemberFunctionForEacher;
class Watch;

class CloudundancyIniValidator
{
   friend class CloudundancyIniValidatorTests;
private:
   // Function Callers
   using _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType =
      MemberFunctionForEacher<CloudundancyIniValidator, fs::path>;
   unique_ptr<const _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType>
      _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder;
   // Constant Components
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const Watch> _watch;
public:
   CloudundancyIniValidator();
   virtual ~CloudundancyIniValidator();
   virtual void ThrowIfZeroDestinationFolderPaths(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
   virtual void AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(
      const CloudundancyIni& cloudundancyIni) const;
private:
   void AppendBackupStartedToCloudundancyLogFileInDestinationFolder(const fs::path& destinationFolderPath) const;
};
