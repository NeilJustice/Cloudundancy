#include "pch.h"
#include "libCloudundancy/Components/DataStructure/Map.h"

struct Struct
{
	int value;
	explicit Struct(int value) : value(value) {}

	friend ostream& operator<<(ostream& os, const Struct&)
	{
		os << "Struct::operator<<";
		return os;
	}

	friend bool operator==(const Struct&, const Struct&)
	{
		return true;
	}

	friend bool operator<(const Struct& left, const Struct& right)
	{
		return left.value < right.value;
	}
};

namespace std
{
	template<>
	struct hash<Struct>
	{
		size_t operator()(const Struct& s) const
		{
			return static_cast<size_t>(s.value);
		}
	};
}

TESTS(MapTests)
AFACT(At_OrderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
AFACT(At_UnorderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
AFACT(ContainsKeyValue_MapDoesNotContainKey_ReturnsFalseFalse)
AFACT(ContainsKeyValue_MapContainsKeyWithValueThatDoesNotMatch_ReturnsTrueFalse)
AFACT(ContainsKeyValue_MapContainsKeyWithValueThatMatches_ReturnsTrueTrue)
AFACT(ContainsKey_ReturnsTrueIfMapContainsKey)
AFACT(TryGetValue_OrderedMap_MapDoesNotContainKey_ReturnsFalseAndDefaultValue)
AFACT(TryGetValue_OrderedMap_MapContainsKey_ReturnsCorrespondingValue)
AFACT(TryGetValue_UnorderedMap_MapDoesNotContainKey_ReturnsFalseAndDefaultValue)
AFACT(TryGetValue_UnorderedMap_MapContainsKey_ReturnsCorrespondingValue)
EVIDENCE

TEST(At_OrderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
{
	map<int, int> m_int_int;
	THROWS_EXCEPTION(Map::At(m_int_int, 0),
		out_of_range, "Key not found in map: [0]");
	m_int_int[0] = 1;
	ARE_EQUAL(1, Map::At(m_int_int, 0));

	map<Struct, string> m_Struct_string;
	THROWS_EXCEPTION(Map::At(m_Struct_string, Struct(0)),
		out_of_range, "Key not found in map: [Struct::operator<<]");
	m_Struct_string[Struct(0)] = "1";
	ARE_EQUAL("1", Map::At(m_Struct_string, Struct(0)));
}

TEST(At_UnorderedMap_ReturnsValueIfKeyPresent_OtherwiseThrows)
{
	unordered_map<int, int> um_int_int;
	THROWS_EXCEPTION(Map::At(um_int_int, 0),
		out_of_range, "Key not found in map: [0]");
	um_int_int[0] = 1;
	ARE_EQUAL(1, Map::At(um_int_int, 0));

	unordered_map<Struct, string> um_Struct_string;
	THROWS_EXCEPTION(Map::At(um_Struct_string, Struct(0)),
		out_of_range, "Key not found in map: [Struct::operator<<]");
	um_Struct_string[Struct(0)] = "1";
	ARE_EQUAL("1", Map::At(um_Struct_string, Struct(0)));
}

TEST(ContainsKeyValue_MapDoesNotContainKey_ReturnsFalseFalse)
{
   const map<int, int> m_int_int;
	//
   const pair<bool, bool> containsKeyValue = Map::ContainsKeyValue(m_int_int, 0, 0);
	//
	ARE_EQUAL(make_pair(false, false), containsKeyValue);
}

TEST(ContainsKeyValue_MapContainsKeyWithValueThatDoesNotMatch_ReturnsTrueFalse)
{
	map<int, int> m_int_int;
	m_int_int[0] = 0;
	//
   const pair<bool, bool> containsKeyValue = Map::ContainsKeyValue(m_int_int, 0, 1);
	//
	ARE_EQUAL(make_pair(true, false), containsKeyValue);
}

TEST(ContainsKeyValue_MapContainsKeyWithValueThatMatches_ReturnsTrueTrue)
{
	map<int, int> m_int_int;
	m_int_int[0] = 0;
	//
   const pair<bool, bool> containsKeyValue = Map::ContainsKeyValue(m_int_int, 0, 0);
	//
	ARE_EQUAL(make_pair(true, true), containsKeyValue);
}

TEST(ContainsKey_ReturnsTrueIfMapContainsKey)
{
	map<int, int> m_int_int;
	IS_FALSE(Map::ContainsKey(m_int_int, 0));

	m_int_int[0] = 0;
	IS_TRUE(Map::ContainsKey(m_int_int, 0));
}

TEST(TryGetValue_OrderedMap_MapDoesNotContainKey_ReturnsFalseAndDefaultValue)
{
   const map<int, int> m_int_int;
	//
   const pair<bool, int> didGetValueAndValue = Map::TryGetValue(m_int_int, 0);
	//
   IS_FALSE(didGetValueAndValue.first);
   IS_ZERO(didGetValueAndValue.second);
}

TEST(TryGetValue_OrderedMap_MapContainsKey_ReturnsCorrespondingValue)
{
   map<int, int> m_int_int;
   const int key = ZenUnit::Random<int>();
   const int value = ZenUnit::Random<int>();
   m_int_int[key] = value;
	//
   const pair<bool, int> didGetValueAndValue = Map::TryGetValue(m_int_int, key);
	//
   IS_TRUE(didGetValueAndValue.first);
   ARE_EQUAL(value, didGetValueAndValue.second);
}

TEST(TryGetValue_UnorderedMap_MapDoesNotContainKey_ReturnsFalseAndDefaultValue)
{
   const unordered_map<int, int> um_int_int;
	//
   const pair<bool, int> didGetValueAndValue = Map::TryGetValue(um_int_int, 0);
	//
	IS_FALSE(didGetValueAndValue.first);
   IS_ZERO(didGetValueAndValue.second);
}

TEST(TryGetValue_UnorderedMap_MapContainsKey_ReturnsCorrespondingValue)
{
   unordered_map<int, int> um_int_int;
   const int key = ZenUnit::Random<int>();
   const int value = ZenUnit::Random<int>();
   um_int_int[key] = value;
	//
   const pair<bool, int> didGetValueAndValue = Map::TryGetValue(um_int_int, key);
	//
   IS_TRUE(didGetValueAndValue.first);
   ARE_EQUAL(value, didGetValueAndValue.second);
}

RUN_TESTS(MapTests)
