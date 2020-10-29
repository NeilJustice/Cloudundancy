#include "pch.h"
#include "libCloudundancy/Utilities/Chars.h"

TESTS(CharsTests)
AFACT(OneOrTwoDigitSizeTToTwoChars_ValueIs0_Writes00)
AFACT(OneOrTwoDigitSizeTToTwoChars_ValueIs1_Writes01)
AFACT(OneOrTwoDigitSizeTToTwoChars_ValueIs12_Writes12)
AFACT(OneOrTwoDigitSizeTToTwoChars_ValueIs99_Writes99)
FACTS(OneOrTwoDigitSizeTToTwoChars_ValueIsGreaterThan99_ThrowsOutOfRangeException)
FACTS(FourDigitSizeTToFourChars_ValueLessThan1000OrGreaterThan9999_ThrowsOutOfRangeException)
AFACT(FourDigitSizeTToFourChars_ValueBetween_1000_WritesValueAsChars)
AFACT(FourDigitSizeTToFourChars_ValueBetween_1200_WritesValueAsChars)
AFACT(FourDigitSizeTToFourChars_ValueBetween_1230_WritesValueAsChars)
AFACT(FourDigitSizeTToFourChars_ValueBetween_1234_WritesValueAsChars)
EVIDENCE

TEST(OneOrTwoDigitSizeTToTwoChars_ValueIs0_Writes00)
{
   char chars[2]{};
   //
   Chars::OneOrTwoDigitSizeTToTwoChars(0, chars);
   //
   ARE_EQUAL('0', chars[0]);
   ARE_EQUAL('0', chars[1]);
}

TEST(OneOrTwoDigitSizeTToTwoChars_ValueIs1_Writes01)
{
   char chars[2]{};
   //
   Chars::OneOrTwoDigitSizeTToTwoChars(1, chars);
   //
   ARE_EQUAL('0', chars[0]);
   ARE_EQUAL('1', chars[1]);
}

TEST(OneOrTwoDigitSizeTToTwoChars_ValueIs12_Writes12)
{
   char chars[2]{};
   //
   Chars::OneOrTwoDigitSizeTToTwoChars(12, chars);
   //
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
}

TEST(OneOrTwoDigitSizeTToTwoChars_ValueIs99_Writes99)
{
   char chars[2]{};
   //
   Chars::OneOrTwoDigitSizeTToTwoChars(99, chars);
   //
   ARE_EQUAL('9', chars[0]);
   ARE_EQUAL('9', chars[1]);
}

TEST1X1(OneOrTwoDigitSizeTToTwoChars_ValueIsGreaterThan99_ThrowsOutOfRangeException,
   size_t value,
   100,
   101)
{
   const string expectedExceptionMessage = "Argument error calling Utils::Chars::OneOrTwoDigitSizeTToTwoChars(size_t value, char* outChars): value must be <= 99: value=" + to_string(value);
   THROWS_EXCEPTION(Chars::OneOrTwoDigitSizeTToTwoChars(value, nullptr),
      out_of_range, expectedExceptionMessage);
}


TEST1X1(FourDigitSizeTToFourChars_ValueLessThan1000OrGreaterThan9999_ThrowsOutOfRangeException,
   size_t value,
   0ull,
   1ull,
   998ull,
   999ull,
   10000ull,
   10001ull)
{
   const string expectedExceptionMessage = "Argument error calling Utils::Chars::FourDigitSizeTToFourChars(size_t value, char* outChars): value must be between 1000 and 9999: value=" + to_string(value);
   THROWS_EXCEPTION(Chars::FourDigitSizeTToFourChars(value, nullptr),
      out_of_range, expectedExceptionMessage);
}

TEST(FourDigitSizeTToFourChars_ValueBetween_1000_WritesValueAsChars)
{
   char chars[4]{};
   //
   Chars::FourDigitSizeTToFourChars(1000ull, chars);
   //
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('0', chars[1]);
   ARE_EQUAL('0', chars[2]);
   ARE_EQUAL('0', chars[3]);
}

TEST(FourDigitSizeTToFourChars_ValueBetween_1200_WritesValueAsChars)
{
   char chars[4]{};
   //
   Chars::FourDigitSizeTToFourChars(1200ull, chars);
   //
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
   ARE_EQUAL('0', chars[2]);
   ARE_EQUAL('0', chars[3]);
}

TEST(FourDigitSizeTToFourChars_ValueBetween_1230_WritesValueAsChars)
{
   char chars[4]{};
   //
   Chars::FourDigitSizeTToFourChars(1230ull, chars);
   //
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
   ARE_EQUAL('3', chars[2]);
   ARE_EQUAL('0', chars[3]);
}

TEST(FourDigitSizeTToFourChars_ValueBetween_1234_WritesValueAsChars)
{
   char chars[4]{};
   //
   Chars::FourDigitSizeTToFourChars(1234ull, chars);
   //
   ARE_EQUAL('1', chars[0]);
   ARE_EQUAL('2', chars[1]);
   ARE_EQUAL('3', chars[2]);
   ARE_EQUAL('4', chars[3]);
}

RUN_TESTS(CharsTests)
