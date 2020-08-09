#include "pch.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"

bool String::Contains(string_view str, string_view substring)
{
   const bool strContainsSubstring = strstr(str.data(), substring.data()) != nullptr;
   return strContainsSubstring;
}

bool String::CaseInsensitiveContains(string_view str, string_view substring)
{
   const string lowercaseStr = String::ToLower(str);
   const string lowercaseSubstring = String::ToLower(substring);
   const bool strContainsSubstring = Contains(lowercaseStr, lowercaseSubstring);
   return strContainsSubstring;
}

string String::ToLower(string_view str)
{
   string lowercaseStr;
   lowercaseStr.resize(str.size());
   std::transform(str.begin(), str.end(), lowercaseStr.begin(), ::tolower);
   return lowercaseStr;
}

std::string String::ReplaceFirst(string_view str, string_view substring, string_view replacement)
{
   const size_t findPosition = str.find(substring);
   if (findPosition == string::npos)
   {
      return string(str);
   }
   string replacedString(str);
   replacedString.replace(findPosition, substring.length(), replacement);
   return replacedString;
}

string String::RegexReplace(const string& str, const string& pattern, const string& replacement)
{
   const regex regexPattern(pattern);
   const string replacedString = regex_replace(str, regexPattern, replacement);
   return replacedString;
}

bool String::StartsWith(string_view str, const string& substring)
{
   const size_t substringLength = substring.size();
	if (substringLength > str.size())
	{
		return false;
	}
	for (size_t i = 0; i < substringLength; ++i)
	{
      const char strChar = str[i];
      const char substringChar = substring[i];
		if (strChar != substringChar)
		{
			return false;
		}
	}
	return true;
}

bool String::EndsWith(const string& str, const string& endsWith)
{
   const size_t strSize = str.size();
   const size_t endsWithSize = endsWith.size();
   if (strSize == 0 || endsWithSize == 0 || endsWithSize > strSize)
   {
      return false;
   }
   const char* const memcmpStartAddress = str.c_str() + strSize - endsWithSize;
   const int memcmpResult = memcmp(memcmpStartAddress, endsWith.c_str(), endsWithSize);
   const bool strEndsWithEndsWith = memcmpResult == 0;
   return strEndsWithEndsWith;
}

vector<string> String::Split(const string& str, char separator)
{
   vector<string> splitString;
   istringstream is(str);
   string token;
   while (getline(is, token, separator))
   {
      splitString.push_back(token);
   }
   return splitString;
}

string String::ToUpper(const string& str)
{
   const size_t strSize = str.size();
   string uppercaseString(strSize, 0);
   for (size_t i = 0; i < strSize; ++i)
   {
      const char c = str[i];
      const bool cIsLowercaseLetter = c >= 'a' && c <= 'z';
      if (cIsLowercaseLetter)
      {
         const char uppercaseLetter = static_cast<char>(static_cast<int>(c) - 32);
         uppercaseString[i] = uppercaseLetter;
      }
      else
      {
         uppercaseString[i] = c;
      }
   }
   return uppercaseString;
}

string String::TrimWhitespace(string_view str)
{
   string stringWithWhitespaceTrimmed(str);
   stringWithWhitespaceTrimmed.erase(0, stringWithWhitespaceTrimmed.find_first_not_of(" \t"));
   stringWithWhitespaceTrimmed.erase(stringWithWhitespaceTrimmed.find_last_not_of(" \t") + 1);
   return stringWithWhitespaceTrimmed;
}

int String::ToInt(const std::string& str)
{
   if (str.empty())
   {
      throw invalid_argument("String::ToInt() called with empty string");
   }
   const bool isNegative = str[0] == '-';
   long long result = 0;
   long long place = 1;
   const int stoppingIndex = isNegative ? 1 : 0;
   for (int i = static_cast<int>(str.size() - 1); i >= stoppingIndex; --i, place *= 10LL)
   {
      char c = str[static_cast<size_t>(i)];
      if (c < '0' || c > '9')
      {
         throw invalid_argument("String::ToInt() called with a string not convertible to a 32-bit integer: \"" + str + "\"");
      }
      const long long digit = static_cast<long long>("0123456789"[c - 48]) - 48LL;
      result += digit * place;
   }
   if (isNegative)
   {
      result *= -1;
   }
   if (result < numeric_limits<int>::min())
   {
      throw invalid_argument(
         "String::ToInt() called with a string containing a number less than std::numeric_limits<int>::min(): \"" + to_string(result) + "\"");
   }
   if (result > numeric_limits<int>::max())
   {
      throw invalid_argument(
         "String::ToInt() called with a string containing a number greater than std::numeric_limits<int>::max(): \"" + to_string(result) + "\"");
   }
   const int integerResult = static_cast<int>(result);
   return integerResult;
}

unsigned String::ToUnsigned(string_view str)
{
	if (str.empty())
	{
		throw invalid_argument("String::ToUnsigned() called with empty string");
	}
	unsigned long long result = 0;
	unsigned long long place = 1;
   for (int i = static_cast<int>(str.size() - 1); i >= 0; --i, place *= 10)
	{
		char c = str[static_cast<size_t>(i)];
		if (c < '0' || c > '9')
		{
			throw invalid_argument("String::ToUnsigned() called with string not convertible to a 32-bit unsigned integer: \"" + string(str) + "\"");
		}
      const unsigned digit = "0123456789"[c - 48] - 48u;
		result += digit * place;
	}
   if (result > numeric_limits<unsigned>::max())
	{
		throw invalid_argument(
			"String::ToUnsigned called with a string containing a number greater than std::numeric_limits<unsigned>::max(): \"" + to_string(result) + "\"");
	}
   const unsigned unsignedValue = static_cast<unsigned>(result);
	return unsignedValue;
}

bool String::ContainsOnlyCharacters(string_view str, const string& validCharacters)
{
   if (validCharacters.empty())
   {
      throw invalid_argument("String::ContainsOnlyCharacters(): validCharacters argument cannot be empty string");
   }
   if (str.empty())
   {
      return false;
   }
   for (char c : str)
   {
      if (validCharacters.find(c) == string::npos)
      {
         return false;
      }
   }
   return true;
}
