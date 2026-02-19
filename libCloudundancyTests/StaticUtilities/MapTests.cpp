#include "pch.h"
#include "libCloudundancy/StaticUtilities/Map.h"

struct TestingStruct
{
   int value;
   explicit TestingStruct(int value) : value(value) {}

   friend ostream& operator<<(ostream& os, const TestingStruct&)
   {
      os << "Struct::operator<<";
      return os;
   }

   friend bool operator==(const TestingStruct&, const TestingStruct&)
   {
      return true;
   }

   friend bool operator<(const TestingStruct& left, const TestingStruct& right)
   {
      return left.value < right.value;
   }
};

namespace std
{
   template<>
   struct hash<TestingStruct>
   {
      size_t operator()(const TestingStruct& testingStruct) const
      {
         const size_t hashValue = static_cast<size_t>(testingStruct.value);
         return hashValue;
      }
   };
}

TESTS(MapTests)
AFACT(At_OrderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
AFACT(At_UnorderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
AFACT(TryGetValue_OrderedMap_MapDoesNotContainKey_DoesNotModifyOutValue_ReturnsFalse)
AFACT(TryGetValue_UnorderedMap_MapDoesNotContainKey_DoesNotModifyOutValue_ReturnsFalse)
EVIDENCE

TEST(At_OrderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
{
   map<int, int> m_int_int;
   THROWS_EXCEPTION(Map::At(m_int_int, 0),
      out_of_range, "Error: Key not found in map: [0]");
   m_int_int[0] = 1;
   ARE_EQUAL(1, Map::At(m_int_int, 0));

   map<TestingStruct, string> m_Struct_string;
   THROWS_EXCEPTION(Map::At(m_Struct_string, TestingStruct(0)),
      out_of_range, "Error: Key not found in map: [Struct::operator<<]");
   m_Struct_string[TestingStruct(0)] = "1";
   ARE_EQUAL("1", Map::At(m_Struct_string, TestingStruct(0)));
}

TEST(At_UnorderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
{
   unordered_map<int, int> um_int_int;
   THROWS_EXCEPTION(Map::At(um_int_int, 0),
      out_of_range, "Error: Key not found in map: [0]");
   um_int_int[0] = 1;
   ARE_EQUAL(1, Map::At(um_int_int, 0));

   unordered_map<TestingStruct, string> um_Struct_string;
   THROWS_EXCEPTION(Map::At(um_Struct_string, TestingStruct(0)),
      out_of_range, "Error: Key not found in map: [Struct::operator<<]");
   um_Struct_string[TestingStruct(0)] = "1";
   ARE_EQUAL("1", Map::At(um_Struct_string, TestingStruct(0)));
}

TEST(TryGetValue_OrderedMap_MapDoesNotContainKey_DoesNotModifyOutValue_ReturnsFalse)
{
   const map<int, int> m_int_int;
   int value = 0;
   //
   const bool mapContainsKey = Map::TryGetValue(m_int_int, 0, value);
   //
   IS_ZERO(value);
   IS_FALSE(mapContainsKey);
}

TEST(TryGetValue_UnorderedMap_MapDoesNotContainKey_DoesNotModifyOutValue_ReturnsFalse)
{
   const unordered_map<int, int> um_int_int;
   int value = 0;
   //
   const bool mapContainsKey = Map::TryGetValue(um_int_int, 0, value);
   //
   IS_ZERO(value);
   IS_FALSE(mapContainsKey);
}

RUN_TESTS(MapTests)
