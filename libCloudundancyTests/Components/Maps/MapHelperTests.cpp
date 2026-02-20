#include "pch.h"
#include "libCloudundancy/Components/Maps/MapHelper.h"

template<typename KeyType, typename ValueType>
TEMPLATE_TESTS(MapHelperTests, KeyType, ValueType)
AFACT(ContainsKeyWithValue_MapDoesNotContainKey_ReturnsFalse)
AFACT(ContainsKeyWithValue_MapContainsKeyWithNonMatchingValue_ReturnsFalse)
AFACT(ContainsKeyWithValue_MapContainsKeyWithMatchingValue_ReturnsTrue)
EVIDENCE

Utils::MapHelper<KeyType, ValueType> _mapHelper;

TEST(ContainsKeyWithValue_MapDoesNotContainKey_ReturnsFalse)
{
   const map<KeyType, ValueType> emptyMap;
   const KeyType key = ZenUnit::Random<KeyType>();
   const ValueType value = ZenUnit::Random<ValueType>();
   //
   const bool containsKeyWithValue = _mapHelper.ContainsKeyWithValue(&emptyMap, key, value);
   //
   IS_FALSE(containsKeyWithValue);
}

TEST(ContainsKeyWithValue_MapContainsKeyWithNonMatchingValue_ReturnsFalse)
{
   const KeyType key = ZenUnit::Random<KeyType>();
   const ValueType value = ZenUnit::Random<ValueType>();
   const ValueType nonMatchingValue = ZenUnit::RandomNotEqualTo<ValueType>(value);
   const map<KeyType, ValueType> nonEmptyMap
   {
      { key, nonMatchingValue }
   };
   //
   const bool containsKeyWithValue = _mapHelper.ContainsKeyWithValue(&nonEmptyMap, key, value);
   //
   IS_FALSE(containsKeyWithValue);
}

TEST(ContainsKeyWithValue_MapContainsKeyWithMatchingValue_ReturnsTrue)
{
   const KeyType key = ZenUnit::Random<KeyType>();
   const ValueType value = ZenUnit::Random<ValueType>();
   const map<KeyType, ValueType> nonEmptyMap
   {
      { key, value }
   };
   //
   const bool containsKeyWithValue = _mapHelper.ContainsKeyWithValue(&nonEmptyMap, key, value);
   //
   IS_TRUE(containsKeyWithValue);
}

RUN_TEMPLATE_TESTS(MapHelperTests, int, int)
THEN_RUN_TEMPLATE_TESTS(MapHelperTests, string, double)
