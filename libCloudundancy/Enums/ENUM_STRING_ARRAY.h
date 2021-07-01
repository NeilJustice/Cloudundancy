#pragma once

#define BEGIN_ENUM_STRING_ARRAY(enumTypeName) constexpr array g_enumStringsArray_##enumTypeName = {
#define ENUM_STRING_ARRAY_ELEMENT(enumValue) #enumValue,
#define END_ENUM_STRING_ARRAY };

#define ENUM_AS_STRING(enumTypeName, enumValue) g_enumStringsArray_##enumTypeName[static_cast<size_t>(enumValue)]
