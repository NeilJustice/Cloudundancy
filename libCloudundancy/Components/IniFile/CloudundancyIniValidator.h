#pragma once

class CloudundancyIniValidator
{
   friend class CloudundancyIniValidatorTests;
private:
   unique_ptr<const Utils::FileSystem> _fileSystem;
public:
   CloudundancyIniValidator();
   virtual ~CloudundancyIniValidator();
   virtual void ThrowIfZeroDestinationFolderPaths(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
};
