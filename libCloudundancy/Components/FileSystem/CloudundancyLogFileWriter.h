#pragma once
class RawFileSystem;

class CloudundancyLogFileWriter
{
   friend class CloudundancyLogFileWriterTests;
private:
   // Constant Comopnents
   unique_ptr<const RawFileSystem> _rawFileSystem;
   unique_ptr<const Watch> _watch;
public:
   CloudundancyLogFileWriter();
   virtual ~CloudundancyLogFileWriter();
   virtual void AppendTextToCloudundancyLogFileInFolder(const fs::path& folderPath, string_view text) const;
};
