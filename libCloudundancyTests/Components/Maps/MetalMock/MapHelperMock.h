#pragma once
#include "libCloudundancy/Components/Maps/MapHelper.h"

namespace Utils
{
   template<typename KeyType, typename ValueType>
   class MapHelperMock : public Metal::Mock<MapHelper<KeyType, ValueType>>
   {
   public:
      using MapType = map<KeyType, ValueType>;

      METALMOCK_NONVOID3_CONST(bool, ContainsKeyWithValue,
         const MapType*,
         const KeyType&,
         const ValueType&)
   };
}
