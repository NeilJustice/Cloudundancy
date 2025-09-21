#include "pch.h"
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"

namespace Utils
{
   const Utils::UtilsRandomGenerator* UtilsRandomGenerator::Instance()
   {
      static const UtilsRandomGenerator utilsRandomGenerator;
      return &utilsRandomGenerator;
   }

   fs::path UtilsRandomGenerator::RelativeFilePath() const
   {
      ostringstream randomFilePathBuilder;
      const int numberOfSubfolders = ZenUnit::RandomBetween<int>(0, 2);
      for (int i = 0; i < numberOfSubfolders; ++i)
      {
         randomFilePathBuilder << ZenUnit::Random<string>() << "/";
      }
      const string fileName = ZenUnit::Random<string>();
      randomFilePathBuilder << fileName;
      const bool hasFileExtension = ZenUnit::Random<bool>();
      if (hasFileExtension)
      {
         randomFilePathBuilder << "." << ZenUnit::Random<string>();
      }
      const string randomFilePathString = randomFilePathBuilder.str();
      fs::path randomFilePath = randomFilePathString;
      return randomFilePath;
   }

   fs::path UtilsRandomGenerator::RelativeFolderPath() const
   {
      ostringstream randomFolderPathBuilder;
      const int numberOfSubfolders = ZenUnit::RandomBetween<int>(0, 2);
      for (int i = 0; i < numberOfSubfolders; ++i)
      {
         randomFolderPathBuilder << ZenUnit::Random<string>() << "/";
      }
      const string folderName = ZenUnit::Random<string>();
      randomFolderPathBuilder << folderName;
      const string randomFolderPathString = randomFolderPathBuilder.str();
      fs::path randomFolderPath = randomFolderPathString;
      return randomFolderPath;
   }

   vector<fs::path> UtilsRandomGenerator::RelativeFolderPaths() const
   {
      const size_t numberOfFolderPaths = ZenUnit::RandomBetween<size_t>(0, 2);
      vector<fs::path> randomRelativeFolderPaths(numberOfFolderPaths);
      for (size_t i = 0; i < numberOfFolderPaths; ++i)
      {
         randomRelativeFolderPaths[i] = RelativeFolderPath();
      }
      return randomRelativeFolderPaths;
   }
}