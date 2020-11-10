#pragma once
struct CloudundancyIni;

class CloudundancyIniValidator
{
public:
   virtual ~CloudundancyIniValidator() = default;
   virtual void ValidateCloudundancyIni(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
};
