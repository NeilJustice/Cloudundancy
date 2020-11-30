#pragma once
struct CloudundancyIni;
template<typename ClassType, typename ElementType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacher;

class CloudundancyIniValidator
{
   friend class CloudundancyIniValidatorTests;
private:
   // Function Callers
   using _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType =
      OneExtraArgMemberFunctionForEacher<CloudundancyIniValidator, fs::path, fs::path>;
   unique_ptr<const _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType>
      _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder;
   // Constant Components
   unique_ptr<const FileSystem> _fileSystem;
public:
   CloudundancyIniValidator();
   virtual ~CloudundancyIniValidator();
   virtual void ThrowIfZeroDestinationFolderPaths(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
   virtual void AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
private:
   void AppendBackupStartedToCloudundancyLogFileInDestinationFolder(
      const fs::path& destinationFolderPath, const fs::path& cloudundancyIniPath) const;
};
