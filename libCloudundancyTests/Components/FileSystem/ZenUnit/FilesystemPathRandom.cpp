#include "pch.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"

namespace ZenUnit
{
   fs::path RandomRelativeFilePath()
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
      const fs::path randomFilePath = randomFilePathString;
      return randomFilePath;
   }

   fs::path RandomRelativeFolderPath()
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
      const fs::path randomFolderPath = randomFolderPathString;
      return randomFolderPath;
   }

   vector<fs::path> RandomRelativeFolderPaths()
   {
      const size_t numberOfFolderPaths = ZenUnit::RandomBetween<size_t>(0, 3);
      vector<fs::path> randomRelativeFolderPaths(numberOfFolderPaths);
      for (size_t i = 0; i < numberOfFolderPaths; ++i)
      {
         randomRelativeFolderPaths[i] = RandomRelativeFolderPath();
      }
      return randomRelativeFolderPaths;
   }
}
