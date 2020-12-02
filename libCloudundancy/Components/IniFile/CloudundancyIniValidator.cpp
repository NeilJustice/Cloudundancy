#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

CloudundancyIniValidator::CloudundancyIniValidator()
   // Constant Components
   : _fileSystem(make_unique<FileSystem>())
{
}

CloudundancyIniValidator::~CloudundancyIniValidator()
{
}

void CloudundancyIniValidator::ThrowIfZeroDestinationFolderPaths(
   const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const
{
   if (cloudundancyIni.destinationFolderPaths.empty())
   {
      const FileSystemException fileSystemException(
         FileSystemExceptionType::MalformedFile, cloudundancyIniPath, "cloudundancyIni.destinationFolderPaths cannot be empty");
      throw fileSystemException;
   }
}

void CloudundancyIniValidator::ThrowIfAnyDestinationFolderIsNotWritableByTheCurrentUser(
   const CloudundancyIni& /*cloudundancyIni*/, const fs::path& /*cloudundancyIniPath*/) const
{

}

// Private Function

void CloudundancyIniValidator::IsFolderWritableByTheCurrentUser(const fs::path& /*folderPath*/) const
{

}
