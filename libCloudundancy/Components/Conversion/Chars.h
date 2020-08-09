#pragma once

class Chars
{
public:
	Chars() = delete;
	static void OneOrTwoDigitUnsignedToTwoChars(unsigned value, char* outChars);
	static void FourDigitUnsignedToFourChars(unsigned value, char* outChars);
};
