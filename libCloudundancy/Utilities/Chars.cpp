#include "pch.h"
#include "libCloudundancy/Utilities/Chars.h"

void Chars::OneOrTwoDigitSizeTToTwoChars(size_t value, char* outChars)
{
   if (value >= 100ull)
   {
      throw out_of_range("Argument error calling Utils::Chars::OneOrTwoDigitSizeTToTwoChars(size_t value, char* outChars): value must be <= 99: value=" + to_string(value));
   }
   if (value < 10ull)
   {
      *outChars = '0';
      *(outChars + 1) = static_cast<char>(value) + '0';
   }
   else
   {
      release_assert(value < 100ull);
      const size_t tensPlace = value / 10ull;
      const size_t onesPlace = value % 10ull;
      *outChars = static_cast<char>(tensPlace) + '0';
      *(outChars + 1) = static_cast<char>(onesPlace) + '0';
   }
}

void Chars::FourDigitSizeTToFourChars(size_t value, char* outChars)
{
   if (value < 1000 || value > 9999)
   {
      throw out_of_range("Argument error calling Utils::Chars::FourDigitSizeTToFourChars(size_t value, char* outChars): value must be between 1000 and 9999: value=" + to_string(value));
   }
   const size_t thousandsPlace = value / 1000ull;
   const size_t hundredsPlace = (value % 1000ull) / 100ull;
   const size_t tensPlace = (value % 100ull) / 10ull;
   const size_t onesPlace = value % 10ull;
   *outChars = static_cast<char>(thousandsPlace) + '0';
   *(outChars + 1) = static_cast<char>(hundredsPlace) + '0';
   *(outChars + 2) = static_cast<char>(tensPlace) + '0';
   *(outChars + 3) = static_cast<char>(onesPlace) + '0';
}
