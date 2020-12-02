#pragma once
struct CloudundancyIni;

class CloudundancyIniValidator
{
   friend class CloudundancyIniValidatorTests;
private:
   unique_ptr<const FileSystem> _fileSystem;
public:
   CloudundancyIniValidator();
   virtual ~CloudundancyIniValidator();
   virtual void ThrowIfZeroDestinationFolderPaths(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
};
