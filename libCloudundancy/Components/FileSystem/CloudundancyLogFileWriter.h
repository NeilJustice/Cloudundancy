#pragma once

class CloudundancyLogFileWriter
{
   friend class CloudundancyLogFileWriterTests;
private:
   // Constant Comopnents
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Utils::Watch> _watch;
public:
   CloudundancyLogFileWriter();
   virtual ~CloudundancyLogFileWriter();
   virtual void AppendTextToCloudundancyLogFileInFolder(const fs::path& folderPath, string_view text) const;
};
