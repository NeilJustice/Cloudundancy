#pragma once
#include "libCloudundancy/Components/Time/date.h"

class UtilsRandomGenerator
{
public:
   virtual fs::path RelativeFilePath() const;
   virtual fs::path RelativeFolderPath() const;
   virtual ~UtilsRandomGenerator() = default;
};
