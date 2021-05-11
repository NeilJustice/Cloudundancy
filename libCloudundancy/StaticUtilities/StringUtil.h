#pragma once

class String
{
public:
	String() = delete;

   template<typename... Types>
	static string ConcatStrings(Types&&... values)
	{
		string concatenatedString;
		string_view stringViews[] = { values... };
		size_t lengthOfAllStrings = 0;
		for (string_view stringView : stringViews)
		{
			const size_t stringViewSize = stringView.size();
			lengthOfAllStrings += stringViewSize;
		}
		concatenatedString.reserve(lengthOfAllStrings);
		for (string_view stringView : stringViews)
		{
			concatenatedString.append(stringView);
		}
		return concatenatedString;
	}

	template<typename... Types>
	static string ConcatValues(const Types&... values)
	{
		ostringstream oss;
		(oss << ... << values);
		string ossConcatenatedValues = oss.str();
		return ossConcatenatedValues;
	}

   static bool Contains(string_view str, string_view substring);
   static bool CaseInsensitiveContains(string_view str, string_view substring);
   static std::string ReplaceFirst(string_view str, string_view substring, string_view replacement);
   static std::string RegexReplace(string_view str, string_view pattern, string_view replacement);
   static bool StartsWith(string_view str, string_view substring);
   static std::vector<std::string> Split(string_view str, char separator);
   static std::string TrimWhitespace(string_view str);
private:
   static string ToLower(string_view str);
};
