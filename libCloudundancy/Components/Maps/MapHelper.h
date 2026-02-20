#pragma once
#include <map>
template<typename KeyType, typename ValueType>
class MapHelperTests;

namespace Utils
{
   template<typename KeyType, typename ValueType>
   class MapHelper
   {
      template<typename _KeyType, typename _ValueType>
      friend class ::MapHelperTests;
   public:
      virtual ~MapHelper() = default;

      virtual bool ContainsKeyWithValue(
         const map<KeyType, ValueType>* m,
         const KeyType& key,
         const ValueType& value) const
      {
         const map<KeyType, ValueType>::const_iterator findIter = m->find(key);
         if (findIter != m->cend())
         {
            bool mapContainsKeyWithValue = findIter->second == value;
            return mapContainsKeyWithValue;
         }
         return false;
      }
   };
}
