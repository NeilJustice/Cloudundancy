#pragma once

class String
{
public:
   static bool Contains(string_view str, string_view substring);
   static bool CaseInsensitiveContains(string_view str, string_view substring);
   static std::string ReplaceFirst(string_view str, string_view substring, string_view replacement);
   static std::string RegexReplace(const std::string& str, const std::string& pattern, const std::string& replacement);
   static bool StartsWith(string_view str, const std::string& substring);
   static int ToInt(const std::string& str);
	static unsigned ToUnsigned(string_view str);
	static std::vector<std::string> Split(const std::string& str, char separator);
   static std::string ToUpper(const std::string& str);
	static std::string TrimWhitespace(string_view str);
   static bool ContainsOnlyCharacters(string_view str, const std::string& validCharacters);

   template<typename T, typename... Ts>
	static std::string Concat(const T& value, const Ts&... values)
	{
		std::ostringstream oss;
		oss << value;
		DoConcat(&oss, values...);
      const std::string result = oss.str();
		return result;
	}

   template<typename T, typename... Ts>
	static void DoConcat(std::ostringstream* outOss, const T& value, const Ts&... values)
	{
		(*outOss) << value;
		DoConcat(outOss, values...);
	}

   template<typename T, typename... Ts>
	static void DoConcat(std::ostringstream* outOss, const T& value)
	{
		(*outOss) << value;
	}

	template<typename... T>
	static void DoConcat(std::ostringstream*)
	{
	}
private:
   static string ToLower(string_view str);
};
