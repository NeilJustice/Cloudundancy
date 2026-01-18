#pragma once

namespace Utils
{
   class UtilsRandomGenerator
   {
   public:
      static const Utils::UtilsRandomGenerator* Instance();
      virtual fs::path RelativeFilePath() const;
      virtual fs::path RelativeFolderPath() const;
      virtual vector<fs::path> RelativeFolderPaths() const;
      virtual ~UtilsRandomGenerator() = default;
   };
}
