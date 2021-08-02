#pragma once

class CloudundancyIniValidator
{
   friend class CloudundancyIniValidatorTests;
private:
   unique_ptr<const Utils::RawFileSystem> _rawFileSystem;
public:
   CloudundancyIniValidator();
   virtual ~CloudundancyIniValidator();
   virtual void ThrowIfZeroDestinationFolderPaths(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
};
