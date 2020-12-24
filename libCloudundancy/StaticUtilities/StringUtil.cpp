#include "pch.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"

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
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4242) // conversion from 'int' to 'char', possible loss of data
#pragma warning(disable: 4244) // '=': conversion from 'int' to 'char', possible loss of data
#endif
   std::transform(str.begin(), str.end(), lowercaseStr.begin(), ::tolower);
#ifdef _WIN32
#pragma warning(pop)
#endif
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

string String::RegexReplace(string_view str, string_view pattern, string_view replacement)
{
   const regex regexPattern(pattern.data());
   string replacedString = regex_replace(str.data(), regexPattern, replacement.data());
   return replacedString;
}

bool String::StartsWith(string_view str, string_view substring)
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

vector<string> String::Split(string_view str, char separator)
{
   vector<string> splitString;
   istringstream is(str.data());
   string token;
   while (getline(is, token, separator))
   {
      splitString.push_back(token);
   }
   return splitString;
}

string String::TrimWhitespace(string_view str)
{
   string stringWithWhitespaceTrimmed(str);
   stringWithWhitespaceTrimmed.erase(0, stringWithWhitespaceTrimmed.find_first_not_of(" \t"));
   stringWithWhitespaceTrimmed.erase(stringWithWhitespaceTrimmed.find_last_not_of(" \t") + 1);
   return stringWithWhitespaceTrimmed;
}
