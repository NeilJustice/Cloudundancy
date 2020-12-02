#pragma once

class CloudundancyLogFileAppender
{
   friend class CloudundancyLogFileAppenderTests;
private:
   // Constant Comopnents
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const Watch> _watch;
public:
   CloudundancyLogFileAppender();
   virtual ~CloudundancyLogFileAppender();
   virtual void AppendTextToCloudundancyLogFileInFolder(
      const fs::path& destinationFolderPath, string_view text) const;
};
