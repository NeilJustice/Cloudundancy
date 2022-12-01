#pragma once
namespace Utils
{
   class UtilsRandomGenerator;
}
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"

namespace ZenUnit
{
   template<>
   class Equalizer<AbsoluteFilePathToRelativeDestinationFolderPath>
   {
   public:
      static void AssertEqual(
         const AbsoluteFilePathToRelativeDestinationFolderPath& expected,
         const AbsoluteFilePathToRelativeDestinationFolderPath& actual);
   };

   AbsoluteFilePathToRelativeDestinationFolderPath TestableRandomAbsoluteFilePathToRelativeDestinationFolderPath(
      const ZenUnit::RandomGenerator* randomGenerator, const Utils::UtilsRandomGenerator* utilsRandomGenerator);
   template<>
   AbsoluteFilePathToRelativeDestinationFolderPath Random<AbsoluteFilePathToRelativeDestinationFolderPath>();
}
