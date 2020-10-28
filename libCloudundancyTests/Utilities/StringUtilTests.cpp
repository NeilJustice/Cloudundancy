#include "pch.h"
#include "libCloudundancy/Utilities/StringUtil.h"

TESTS(StringTests)
FACTS(Contains_ReturnsTrueIfStringContainsSubstring)
FACTS(CaseInsensitiveContains_ReturnsTrueIfStringCaseInsensitiveContainsSubstring)
FACTS(ReplaceFirst_ReturnsReplacedString)
FACTS(RegexReplace_ReturnsRegexReplacedString)
FACTS(StartsWith_ReturnsTrueIfStringStartsWithSubstring)
FACTS(Split_ReturnsStringSplitOnCharacterSeparator)
FACTS(TrimWhitespace_ReturnsStringWithLeadingAndTrailingSpacesAndTabsRemoved)
AFACT(Concat_ConcatsValuesIntoString)
AFACT(ContainsOnlyCharacters_ValidCharactersEmptyString_Throws)
FACTS(ContainsOnlyCharacters_ReturnsTrueIfStringContainsOnlySpecifiedValidCharacters)
AFACT(ToInt_EmptyString_Throws)
FACTS(ToInt_StringNotConvertibleToInt_Throws)
FACTS(ToInt_StringIsValueLessThanThanIntMin_Throws)
FACTS(ToInt_StringIsValueGreaterThanIntMax_Throws)
FACTS(ToInt_StringIsValidInt_ReturnsInt)
AFACT(ToUnsigned_EmptyString_Throws)
FACTS(ToUnsigned_StringNotConvertibleToUnsigned_Throws)
FACTS(ToUnsigned_StringIsValueGreaterThanUnsignedMax_Throws)
FACTS(ToUnsigned_StringIsInRangeUnsignedNumber_ReturnsNumber)
FACTS(ToUpper_ReturnsStringAllUppercase)
EVIDENCE

struct UserType
{
	int x;
	explicit UserType(int x) : x(x) {}
	friend ostream& operator<<(ostream& os, const UserType& userType)
	{
		os << userType.x;
		return os;
	}
};

TEST3X3(Contains_ReturnsTrueIfStringContainsSubstring,
   bool expectedReturnValue, const string& str, const string& substring,
   true, "", "",
   true, " ", "",
   true, " ", " ",
   true, "  ", " ",
   false, "", " ",
   true, "abc", "abc",
   false, "Abc", "abc",
   true, "abc", "ab",
   true, "abc", "bc",
   true, "abc def ghi", "c d",
   true, "a\r\n_bc_", "bc")
{
   ARE_EQUAL(expectedReturnValue, String::Contains(str, substring));
}

TEST3X3(CaseInsensitiveContains_ReturnsTrueIfStringCaseInsensitiveContainsSubstring,
   bool expectedReturnValue, const string& str, const string& substring,
   true, "", "",
   true, " ", "",
   true, " ", " ",
   true, "  ", " ",
   false, "", " ",
   true, "abc", "abc",
   true, "ABC", "abc",
   true, "abc", "ABC",
   true, "abc", "ab",
   true, "abc", "bc",
   true, "abc def ghi", "c d",
   true, "a\r\n_bc_", "bc")
{
   ARE_EQUAL(expectedReturnValue, String::CaseInsensitiveContains(str, substring));
}

TEST4X4(ReplaceFirst_ReturnsReplacedString,
   const string& str, const string& substring, const string& replacement, const string& expectedReturnValue,
   "", "", "", "",
   "a", "b", "", "a",
   "a", "A", "", "a",
   "\r\n\r\n", "\r", "", "\n\r\n",
   "aa", "a", "b", "ba",
   "C:\\Folder\\Subfolder\\File.ext", "C:\\Folder\\Subfolder\\", "", "File.ext",
   " 1 2 3 3 ", " 3 ", " 4 ", " 1 2 4 3 ")
{
   const string replacedString = String::ReplaceFirst(str, substring, replacement);
   ARE_EQUAL(expectedReturnValue, replacedString);
}

TEST4X4(RegexReplace_ReturnsRegexReplacedString,
   const string& str, const string& pattern, const string& replacement, const string& expectedReturnValue,
   "", "", "", "",
   "a", "b", "c", "a",
   "a", "a", "b", "b",
   "A", "a", "b", "A",
   "123 -> 456", "\\d\\d\\d -> ", "|", "|456")
{
   const string replacedString = String::RegexReplace(str, pattern, replacement);
   ARE_EQUAL(expectedReturnValue, replacedString);
}

TEST3X3(StartsWith_ReturnsTrueIfStringStartsWithSubstring,
   const string& str, const string& substring, bool expectedReturnValue,
   string(), string(), true,
   "", " ", false,
   "", "a", false,
   "a", "aa", false,
   "A", "a", false,
   " aa", "aa", false,
   " aa", "aa", false,
   "aa", "a", true,
   "aa", "aa", true)
{
   ARE_EQUAL(expectedReturnValue, String::StartsWith(str, substring));
}

TEST3X3(Split_ReturnsStringSplitOnCharacterSeparator,
   const string& str, char separator, const vector<string>& expectedReturnValue,
   "", '\0', vector<string>{},
   "", ',', vector<string>{},
   ",", ',', vector<string>{""},
   "|", '|', vector<string>{""},
   "a", ',', vector<string>{"a"},
   "a,b,c", ',', vector<string>{"a", "b", "c"},
   ",a,b,,c,", ',', vector<string>{"", "a", "b", "", "c"},
   "a", '|', vector<string>{"a"},
   "a|b|c", '|', vector<string>{"a", "b", "c"},
   ",a|b|c||", '|', vector<string>{",a", "b", "c", ""})
{
   const vector<string> splitString = String::Split(str, separator);
   VECTORS_ARE_EQUAL(expectedReturnValue, splitString);
}

TEST2X2(TrimWhitespace_ReturnsStringWithLeadingAndTrailingSpacesAndTabsRemoved,
   const string& str, const string& expectedReturnValue,
   "", "",
   " \t ", "",
   " \tabc \t", "abc",
   " \t \t TextA \t TextB \t ", "TextA \t TextB")
{
	const string strWithWhitespaceTrimmed = String::TrimWhitespace(str);
	ARE_EQUAL(expectedReturnValue, strWithWhitespaceTrimmed);
}

TEST(Concat_ConcatsValuesIntoString)
{
	ARE_EQUAL("", String::Concat(""));
	ARE_EQUAL("1", String::Concat("1"));
	ARE_EQUAL("12", String::Concat("1", "2"));
	ARE_EQUAL("123", String::Concat("1", "2", "3"));

   const UserType userType1(1);
   const string str = "hello";
   const UserType userType3(3);
	ARE_EQUAL("1hello3", String::Concat(userType1, str, userType3));
}

TEST(ContainsOnlyCharacters_ValidCharactersEmptyString_Throws)
{
   THROWS_EXCEPTION(String::ContainsOnlyCharacters("str", ""),
      invalid_argument, "String::ContainsOnlyCharacters(): validCharacters argument cannot be empty string");
}

TEST3X3(ContainsOnlyCharacters_ReturnsTrueIfStringContainsOnlySpecifiedValidCharacters,
   const string& str, const string& validCharacters, bool expectedReturnValue,
   "", "a", false,
   "a", "b", false,
   "a", "A", false,
   " 10.50", ".0123456789", false,
   "10.50abc", ".0123456789", false,
   "10.50", ".0123456789", true,
   "a b\tc", "cba \tyxz", true)
{
   ARE_EQUAL(expectedReturnValue, String::ContainsOnlyCharacters(str, validCharacters));
}

TEST(ToInt_EmptyString_Throws)
{
   THROWS_EXCEPTION(String::ToInt(""),
      invalid_argument, "String::ToInt() called with empty string");
}

TEST1X1(ToInt_StringNotConvertibleToInt_Throws,
   const string& str,
   " ",
   "a",
   "--1",
   "0.0",
   "1.1",
   " 1",
   "  0",
   "1 ",
   "0  ")
{
   THROWS_EXCEPTION(String::ToInt(str), invalid_argument,
      "String::ToInt() called with a string not convertible to a 32-bit integer: \"" + str + "\"");
}

TEST1X1(ToInt_StringIsValueLessThanThanIntMin_Throws,
   const string& str,
   to_string(static_cast<long long>(numeric_limits<int>::min()) - 1),
   to_string(static_cast<long long>(numeric_limits<int>::min()) - 2))
{
   THROWS_EXCEPTION(String::ToInt(str), invalid_argument,
      "String::ToInt() called with a string containing a number less than std::numeric_limits<int>::min(): \"" + str + "\"");
}

TEST1X1(ToInt_StringIsValueGreaterThanIntMax_Throws,
   const string& str,
   to_string(static_cast<long long>(numeric_limits<int>::max()) + 1),
   to_string(static_cast<long long>(numeric_limits<int>::max()) + 2))
{
   THROWS_EXCEPTION(String::ToInt(str), invalid_argument,
      "String::ToInt() called with a string containing a number greater than std::numeric_limits<int>::max(): \"" + str + "\"");
}

TEST2X2(ToInt_StringIsValidInt_ReturnsInt,
   const string& str, int expectedReturnValue,
   to_string(numeric_limits<int>::min()), numeric_limits<int>::min(),
   to_string(numeric_limits<int>::min() + 1), numeric_limits<int>::min() + 1,
   "-01234567890", -1234567890,
   "-1234567890", -1234567890,
   "-123456789", -123456789,
   "-12345678", -12345678,
   "-1234567", -1234567,
   "-123456", -123456,
   "-12345", -12345,
   "-1234", -1234,
   "-123", -123,
   "-12", -12,
   "-1", -1,
   "-00", 0,
   "-0", 0,
   "0", 0,
   "00", 0,
   "1", 1,
   "12", 12,
   "123", 123,
   "1234", 1234,
   "12345", 12345,
   "123456", 123456,
   "1234567", 1234567,
   "12345678", 12345678,
   "123456789", 123456789,
   "1234567890", 1234567890,
   "01234567890", 1234567890,
   to_string(numeric_limits<int>::max() - 1), numeric_limits<int>::max() - 1,
   to_string(numeric_limits<int>::max()), numeric_limits<int>::max())
{
   ARE_EQUAL(expectedReturnValue, String::ToInt(str));
}

TEST(ToUnsigned_EmptyString_Throws)
{
   THROWS_EXCEPTION(String::ToUnsigned(""),
      invalid_argument, "String::ToUnsigned() called with empty string");
}

TEST1X1(ToUnsigned_StringNotConvertibleToUnsigned_Throws,
   string_view str,
   " ",
   "a",
   "-1",
   "-0",
   "0.0",
   "1.1",
   " 1",
   "  0",
   "1 ",
   "0  ")
{
	THROWS_EXCEPTION(String::ToUnsigned(str), invalid_argument,
      "String::ToUnsigned() called with string not convertible to a 32-bit unsigned integer: \"" + string(str) + "\"");
}

TEST1X1(ToUnsigned_StringIsValueGreaterThanUnsignedMax_Throws,
   string_view expectedGreaterThanUnsignedMaxValue,
   to_string(static_cast<unsigned long long>(numeric_limits<unsigned>::max()) + 1ull),
   to_string(static_cast<unsigned long long>(numeric_limits<unsigned>::max()) + 2ull))
{
	THROWS_EXCEPTION(String::ToUnsigned(expectedGreaterThanUnsignedMaxValue),
      invalid_argument, "String::ToUnsigned called with a string containing a number greater than std::numeric_limits<unsigned>::max(): \""
         + string(expectedGreaterThanUnsignedMaxValue) + "\"");
}

TEST2X2(ToUnsigned_StringIsInRangeUnsignedNumber_ReturnsNumber,
   const string& str, unsigned expectedReturnValue,
   "0", 0u,
   "00", 0u,
   "1", 1u,
   "12", 12u,
   "123", 123u,
   "1234", 1234u,
   "12345", 12345u,
   "123456", 123456u,
   "1234567", 1234567u,
   "12345678", 12345678u,
   "123456789", 123456789u,
   "1234567890", 1234567890u,
   "01234567890", 1234567890u,
   to_string(numeric_limits<unsigned int>::max() - 1), numeric_limits<unsigned int>::max() - 1,
   to_string(numeric_limits<unsigned int>::max()), numeric_limits<unsigned int>::max())
{
   ARE_EQUAL(expectedReturnValue, String::ToUnsigned(str));
}

TEST2X2(ToUpper_ReturnsStringAllUppercase,
   const string& str, const string& expectedReturnValue,
   "", "",
   " \t\r\n ", " \t\r\n ",
   "a", "A",
   "A", "A",
   "aBc", "ABC",
   "ABC", "ABC",
   "1234567890_a_!@#$%^&*()_+", "1234567890_A_!@#$%^&*()_+")
{
   const string uppercaseStr = String::ToUpper(str);
   ARE_EQUAL(expectedReturnValue, uppercaseStr);
}

RUN_TESTS(StringTests)
