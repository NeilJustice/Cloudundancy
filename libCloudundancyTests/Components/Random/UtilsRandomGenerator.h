#pragma once
#include "libCloudundancy/Components/Time/date.h"

class UtilsRandomGenerator
{
public:
   static const UtilsRandomGenerator* Instance();
   virtual fs::path RelativeFilePath() const;
   virtual fs::path RelativeFolderPath() const;
   virtual vector<fs::path> RelativeFolderPaths() const;
   virtual ~UtilsRandomGenerator() = default;
};
