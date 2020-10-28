#include "pch.h"
#include "libCloudundancy/Components/Conversion/Chars.h"

void Chars::OneOrTwoDigitUnsignedToTwoChars(unsigned value, char* outChars)
{
	if (value >= 100)
	{
		throw out_of_range("Argument error calling Chars::OneOrTwoDigitUnsignedToTwoChars(unsigned value, char* outChars): value must be <= 99: value=" + to_string(value));
	}
	if (value < 10)
	{
		*outChars = '0';
      *(outChars + 1) = static_cast<char>(value) + '0';
	}
	else
	{
		release_assert(value < 100u);
      const unsigned tensPlace = value / 10u;
      const unsigned onesPlace = value % 10u;
		*outChars = static_cast<char>(tensPlace) + '0';
		*(outChars + 1) = static_cast<char>(onesPlace) + '0';
	}
}

void Chars::FourDigitUnsignedToFourChars(unsigned value, char* outChars)
{
	if (value < 1000 || value > 9999)
	{
		throw out_of_range("Argument error calling Chars::FourDigitUnsignedToFourChars(unsigned value, char* outChars): value must be between 1000 and 9999: value=" + to_string(value));
	}
   const unsigned thousandsPlace = value / 1000u;
   const unsigned hundredsPlace = (value % 1000u) / 100u;
   const unsigned tensPlace = (value % 100u) / 10u;
   const unsigned onesPlace = value % 10u;
	*outChars = static_cast<char>(thousandsPlace) + '0';
	*(outChars + 1) = static_cast<char>(hundredsPlace) + '0';
	*(outChars + 2) = static_cast<char>(tensPlace) + '0';
	*(outChars + 3) = static_cast<char>(onesPlace) + '0';
}
