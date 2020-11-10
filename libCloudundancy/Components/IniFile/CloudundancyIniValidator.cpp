#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

void CloudundancyIniValidator::ValidateCloudundancyIni(
   const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const
{
   if (cloudundancyIni.destinationFolderPaths.empty())
   {
      const FileSystemException fileSystemException(
         FileSystemExceptionType::MalformedFile, cloudundancyIniPath, "cloudundancyIni.destinationFolderPaths cannot be empty");
      throw fileSystemException;
   }
}
