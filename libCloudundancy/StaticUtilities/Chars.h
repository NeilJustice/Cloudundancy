#pragma once

class Chars
{
public:
   Chars() = delete;
   static void OneOrTwoDigitSizeTToTwoChars(size_t value, char* outChars);
   static void FourDigitSizeTToFourChars(size_t value, char* outChars);
};
