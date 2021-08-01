#include "pch.h"
#include "libCloudundancy/StaticUtilities/Chars.h"

void Chars::OneOrTwoDigitSizeTToTwoChars(size_t value, char* outChars)
{
   if (value >= 100ULL)
   {
      throw out_of_range("Argument error calling Chars::OneOrTwoDigitSizeTToTwoChars(size_t value, char* outChars): value must be <= 99: value=" + to_string(value));
   }
   if (value < 10ULL)
   {
      *outChars = '0';
      *(outChars + 1) = static_cast<char>(value) + '0';
   }
   else
   {
      release_assert(value < 100ULL);
      const size_t tensPlace = value / 10ULL;
      const size_t onesPlace = value % 10ULL;
      *outChars = static_cast<char>(tensPlace) + '0';
      *(outChars + 1) = static_cast<char>(onesPlace) + '0';
   }
}

void Chars::FourDigitSizeTToFourChars(size_t value, char* outChars)
{
   if (value < 1000 || value > 9999)
   {
      throw out_of_range("Argument error calling Chars::FourDigitSizeTToFourChars(size_t value, char* outChars): value must be between 1000 and 9999: value=" + to_string(value));
   }
   const size_t thousandsPlace = value / 1000ULL;
   const size_t hundredsPlace = (value % 1000ULL) / 100ULL;
   const size_t tensPlace = (value % 100ULL) / 10ULL;
   const size_t onesPlace = value % 10ULL;
   *outChars = static_cast<char>(thousandsPlace) + '0';
   *(outChars + 1) = static_cast<char>(hundredsPlace) + '0';
   *(outChars + 2) = static_cast<char>(tensPlace) + '0';
   *(outChars + 3) = static_cast<char>(onesPlace) + '0';
}
