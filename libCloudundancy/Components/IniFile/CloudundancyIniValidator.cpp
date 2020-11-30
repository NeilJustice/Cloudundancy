#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberFunctionForEacher.h"

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

void CloudundancyIniValidator::ThrowIfAnyDestinationFoldersNotWritable(
   const CloudundancyIni& /*cloudundancyIni*/, const fs::path& /*cloudundancyIniPath*/) const
{
   // _forEacher_ThrowIfFolderIsNotWritable->MemberFunctionForEach(
   //  cloudundancyIni.destinationFolderPaths, &CloudundancyIniValidator::ThrowIfFolderIsNotWritable, this, cloudundancyIniPath);
}

// Private Functions

void CloudundancyIniValidator::ThrowIfFolderNotWritable(
   const fs::path& /*folderPath*/, const fs::path& /*cloudundancyIniPath*/) const
{

}
