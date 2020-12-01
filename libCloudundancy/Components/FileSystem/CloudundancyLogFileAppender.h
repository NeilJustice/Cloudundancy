#pragma once

class CloudundancyLogFileAppender
{
   friend class CloudundancyLogFileAppenderTests;
private:
   // Function Callers
   using _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderType =
      OneExtraArgMemberFunctionForEacher<CloudundancyLogFileAppender, fs::path, string_view>;
   unique_ptr<const _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolderType>
      _oneExtraArgMemberForEacher_AppendTextToCloudundancyLogFileInDestinationFolder;
   // Constant Comopnents
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const Watch> _watch;
public:
   CloudundancyLogFileAppender();
   virtual ~CloudundancyLogFileAppender();
   virtual void AppendBackupStartedToCloudundancyLogFilesInAllDestinationFolders(
      const vector<fs::path>& destinationFolderPaths) const;
   virtual void AppendTextToCloudundancyLogFileInDestinationFolder(
      const fs::path& destinationFolderPath, string_view text) const;
};
