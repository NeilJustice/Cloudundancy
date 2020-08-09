#pragma once
#include "libCloudundancy/Components/DataStructure/Map.h"

#define BEGIN_STRING_ENUM_MAP(enumTypeName) \
	class StringEnumMap_##enumTypeName \
	{ \
   private: \
      static std::unordered_map<std::string, enumTypeName> stringToEnumMap; \
		static std::unordered_map<enumTypeName, std::string> enumToStringMap; \
   public: \
      static enumTypeName StringToEnum(const std::string& str) \
		{ \
			PopulateMapsIfUnpopulated(); \
			const enumTypeName stringAsEnum = Map::At(StringEnumMap_##enumTypeName::stringToEnumMap, str); \
         return stringAsEnum; \
		} \
		static std::string EnumToString(enumTypeName enumValue) \
		{ \
			PopulateMapsIfUnpopulated(); \
			const std::string enumAsString = Map::At(StringEnumMap_##enumTypeName::enumToStringMap, enumValue); \
         return enumAsString; \
		} \
   private: \
		static void PopulateMapsIfUnpopulated() \
		{ \
			if (!enumToStringMap.empty()) return;

#define ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(enumClassName, enumValueName) \
	enumToStringMap[enumClassName::enumValueName] = #enumValueName; \
	stringToEnumMap[#enumClassName "::" #enumValueName] = enumClassName::enumValueName;

#define END_STRING_ENUM_MAP } };

#define INITIALIZE_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPS(enumTypeName) \
	std::unordered_map<enumTypeName, std::string> StringEnumMap_##enumTypeName::enumToStringMap; \
	std::unordered_map<std::string, enumTypeName> StringEnumMap_##enumTypeName::stringToEnumMap;

#define STRING_TO_ENUM(enumTypeName, str) StringEnumMap_##enumTypeName::StringToEnum(str)
#define ENUM_TO_STRING(enumTypeName, enumValue) StringEnumMap_##enumTypeName::EnumToString(enumValue)
