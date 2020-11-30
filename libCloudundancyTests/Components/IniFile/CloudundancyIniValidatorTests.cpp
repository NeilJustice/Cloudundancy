#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

TESTS(CloudundancyIniValidatorTests)
AFACT(ThrowIfZeroDestinationFolderPaths_DestinationFolderPathsIsEmpty_ThrowsFileSystemExceptionWithReasonMalformedFile)
EVIDENCE

CloudundancyIniValidator _cloudundancyIniValidator;

TEST(ThrowIfZeroDestinationFolderPaths_DestinationFolderPathsIsEmpty_ThrowsFileSystemExceptionWithReasonMalformedFile)
{
   CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   cloudundancyIni.destinationFolderPaths = {};
   //
   const fs::path cloudundancyIniPath = ZenUnit::Random<fs::path>();
   const FileSystemException expectedFileSystemException(
      FileSystemExceptionType::MalformedFile, cloudundancyIniPath, "cloudundancyIni.destinationFolderPaths cannot be empty");
   const string expectedExceptionMessage = expectedFileSystemException.what();
   THROWS_EXCEPTION(_cloudundancyIniValidator.ThrowIfZeroDestinationFolderPaths(cloudundancyIni, cloudundancyIniPath),
      FileSystemException, expectedExceptionMessage);
}

RUN_TESTS(CloudundancyIniValidatorTests)
