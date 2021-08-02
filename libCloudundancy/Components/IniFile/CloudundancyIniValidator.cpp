#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

CloudundancyIniValidator::CloudundancyIniValidator()
   // Constant Components
   : _rawFileSystem(make_unique<Utils::RawFileSystem>())
{
}

CloudundancyIniValidator::~CloudundancyIniValidator()
{
}

void CloudundancyIniValidator::ThrowIfZeroDestinationFolderPaths(const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const
{
   if (cloudundancyIni.destinationFolderPaths.empty())
   {
      const Utils::FileMalformedException fileMalformedException(cloudundancyIniPath, "cloudundancyIni.destinationFolderPaths cannot be empty");
      throw fileMalformedException;
   }
}
