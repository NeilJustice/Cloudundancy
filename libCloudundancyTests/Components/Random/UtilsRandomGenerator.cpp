#include "pch.h"
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"

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
