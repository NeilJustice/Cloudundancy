#include "pch.h"
#include "libCloudundancy/Components/Conversion/Chars.h"

TESTS(CharsTests)
AFACT(OneOrTwoDigitIntToTwoChars_0_Writes00)
AFACT(OneOrTwoDigitIntToTwoChars_1_Writes01)
AFACT(OneOrTwoDigitIntToTwoChars_12_Writes11)
FACTS(OneOrTwoDigitIntToTwoChars_ValueGTE100_ThrowsOutOfRangeException)
FACTS(FourDigitUnsignedToFourChars_ValueLessThan1000OrGreaterThan9999_ThrowsOutOfRangeException)
AFACT(FourDigitUnsignedToFourChars_ValueBetween_1000_WritesValueAsChars)
AFACT(FourDigitUnsignedToFourChars_ValueBetween_1200_WritesValueAsChars)
AFACT(FourDigitUnsignedToFourChars_ValueBetween_1230_WritesValueAsChars)
AFACT(FourDigitUnsignedToFourChars_ValueBetween_1234_WritesValueAsChars)
EVIDENCE

TEST(OneOrTwoDigitIntToTwoChars_0_Writes00)
{
	char chars[2]{};
	//
   Chars::OneOrTwoDigitUnsignedToTwoChars(0u, chars);
	//
   ARE_EQUAL('0', chars[0]);
   ARE_EQUAL('0', chars[1]);
}

TEST(OneOrTwoDigitIntToTwoChars_1_Writes01)
{
	char chars[2]{};
	//
   Chars::OneOrTwoDigitUnsignedToTwoChars(1u, chars);
	//
   ARE_EQUAL('0', chars[0]);
   ARE_EQUAL('1', chars[1]);
}

TEST(OneOrTwoDigitIntToTwoChars_12_Writes11)
{
	char chars[2]{};
	//
   Chars::OneOrTwoDigitUnsignedToTwoChars(12u, chars);
	//
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
}

TEST1X1(OneOrTwoDigitIntToTwoChars_ValueGTE100_ThrowsOutOfRangeException,
   unsigned value,
   100u,
   101u)
{
   const string expectedExceptionMessage = "Argument error calling Chars::OneOrTwoDigitUnsignedToTwoChars(unsigned value, char* outChars): value must be <= 99: value=" + to_string(value);
	THROWS_EXCEPTION(Chars::OneOrTwoDigitUnsignedToTwoChars(value, nullptr),
      out_of_range, expectedExceptionMessage);
}

TEST1X1(FourDigitUnsignedToFourChars_ValueLessThan1000OrGreaterThan9999_ThrowsOutOfRangeException,
   unsigned value,
   0u,
   1u,
   998u,
   999u,
   10000u,
   10001u)
{
   const string expectedExceptionMessage = "Argument error calling Chars::FourDigitUnsignedToFourChars(unsigned value, char* outChars): value must be between 1000 and 9999: value=" + to_string(value);
   THROWS_EXCEPTION(Chars::FourDigitUnsignedToFourChars(value, nullptr),
      out_of_range, expectedExceptionMessage);
}

TEST(FourDigitUnsignedToFourChars_ValueBetween_1000_WritesValueAsChars)
{
	char chars[4]{};
   Chars::FourDigitUnsignedToFourChars(1000u, chars);
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('0', chars[1]);
   ARE_EQUAL('0', chars[2]);
   ARE_EQUAL('0', chars[3]);
}

TEST(FourDigitUnsignedToFourChars_ValueBetween_1200_WritesValueAsChars)
{
	char chars[4]{};
   Chars::FourDigitUnsignedToFourChars(1200u, chars);
	ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
   ARE_EQUAL('0', chars[2]);
   ARE_EQUAL('0', chars[3]);
}

TEST(FourDigitUnsignedToFourChars_ValueBetween_1230_WritesValueAsChars)
{
	char chars[4]{};
   Chars::FourDigitUnsignedToFourChars(1230u, chars);
	ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
   ARE_EQUAL('3', chars[2]);
   ARE_EQUAL('0', chars[3]);
}

TEST(FourDigitUnsignedToFourChars_ValueBetween_1234_WritesValueAsChars)
{
	char chars[4]{};
   Chars::FourDigitUnsignedToFourChars(1234u, chars);
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
   ARE_EQUAL('3', chars[2]);
   ARE_EQUAL('4', chars[3]);
}

RUN_TESTS(CharsTests)
