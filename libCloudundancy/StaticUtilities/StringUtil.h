#pragma once

class String
{
public:
	String() = delete;

   static bool Contains(string_view str, string_view substring);
   static bool CaseInsensitiveContains(string_view str, string_view substring);
   static std::string ReplaceFirst(string_view str, string_view substring, string_view replacement);
   static std::string RegexReplace(string_view str, string_view pattern, string_view replacement);
   static bool StartsWith(string_view str, string_view substring);
   static std::vector<std::string> Split(string_view str, char separator);
   static std::string TrimWhitespace(string_view str);

   template<typename... Types>
   static std::string Concat(const Types&... values)
	{
		std::ostringstream oss;
		(oss << ... << values);
      const std::string ossConcatenatedValues = oss.str();
		return ossConcatenatedValues;
	}
private:
   static string ToLower(string_view str);
};
