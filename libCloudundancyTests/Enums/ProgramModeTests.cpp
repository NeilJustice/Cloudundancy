#include "pch.h"
#include "libCloudundancy/Enums/ProgramMode.h"

TESTS(ProgramModeTests)
AFACT(ENUM_AS_STRING_ReturnsEnumAsStringView)
AFACT(OStreamInsertionOperator_WritesEnumAsStringViewToOStream_ReturnsOStream)
EVIDENCE

static void AssertEnumAsStringView(ProgramMode programMode, string_view expectedEnumTypeStringView)
{
   const string_view enumTypeStringView = ENUM_AS_STRING(ProgramMode, programMode);
   ARE_EQUAL(expectedEnumTypeStringView, enumTypeStringView);
}

TEST(ENUM_AS_STRING_ReturnsEnumAsStringView)
{
   AssertEnumAsStringView(ProgramMode::Unset, "Unset");
   AssertEnumAsStringView(ProgramMode::MaxValue, "MaxValue");
}

TEST(OStreamInsertionOperator_WritesEnumAsStringViewToOStream_ReturnsOStream)
{
   ostringstream oss;
   //
   oss << ProgramMode::Unset << ' ' << ProgramMode::MaxValue;
   //
   const string str = oss.str();
   ARE_EQUAL("Unset MaxValue", str);
}

RUN_TESTS(ProgramModeTests)
