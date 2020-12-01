#pragma once
template<typename ClassType, typename ElementType>
class MemberFunctionForEacher;
class Watch;

class CloudundancyLogFileAppender
{
   friend class CloudundancyLogFileAppenderTests;
private:
   // Function Callers
   using _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType =
      MemberFunctionForEacher<CloudundancyLogFileAppender, fs::path>;
   unique_ptr<const _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolderType>
      _memberForEacher_AppendBackupStartedToCloudundancyLogFileInDestinationFolder;
   // Constant Comopnents
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const Watch> _watch;
public:
   CloudundancyLogFileAppender();
   virtual ~CloudundancyLogFileAppender();
   virtual void AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(
      const vector<fs::path>& destinationFolderPaths) const;
private:
   void AppendBackupStartedToCloudundancyLogFileInDestinationFolder(const fs::path& destinationFolderPath) const;
};
