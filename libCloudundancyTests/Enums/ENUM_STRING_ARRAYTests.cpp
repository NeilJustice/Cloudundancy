#include "pch.h"
#include "libCloudundancy/Enums/ENUM_STRING_ARRAY.h"

enum class TestingEnum
{
   A,
   B,
   C,
   MaxValue
};

BEGIN_ENUM_STRING_ARRAY(TestingEnum)
ENUM_STRING_ARRAY_ELEMENT(A)
ENUM_STRING_ARRAY_ELEMENT(B)
ENUM_STRING_ARRAY_ELEMENT(C_couldBeAnyString)
ENUM_STRING_ARRAY_ELEMENT(MaxValue)
END_ENUM_STRING_ARRAY

TESTS(ENUM_STRING_ARRAYTests)
AFACT(GlobalEnumStringsArrayIndices_ReturnExpectedValues)
EVIDENCE

TEST(GlobalEnumStringsArrayIndices_ReturnExpectedValues)
{
   const TestingEnum testingEnumA = TestingEnum::A;
   ARE_EQUAL("A", ENUM_AS_STRING(TestingEnum, testingEnumA));

   const TestingEnum testingEnumB = TestingEnum::B;
   ARE_EQUAL("B", ENUM_AS_STRING(TestingEnum, testingEnumB));

   const TestingEnum testingEnumC = TestingEnum::C;
   ARE_EQUAL("C_couldBeAnyString", ENUM_AS_STRING(TestingEnum, testingEnumC));

   const TestingEnum testingEnumMaxValue = TestingEnum::MaxValue;
   ARE_EQUAL("MaxValue", ENUM_AS_STRING(TestingEnum, testingEnumMaxValue));
}

RUN_TESTS(ENUM_STRING_ARRAYTests)
