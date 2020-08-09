#include "pch.h"
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"

fs::path UtilsRandomGenerator::RelativeFilePath() const
{
   const fs::path randomRelativeFilePath = ZenUnit::RandomRelativeFilePath();
   return randomRelativeFilePath;
}

fs::path UtilsRandomGenerator::RelativeFolderPath() const
{
   const fs::path randomRelativeFolderPath = ZenUnit::RandomRelativeFolderPath();
   return randomRelativeFolderPath;
}
