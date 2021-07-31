#include "pch.h"
#include "libCloudundancy/StaticUtilities/StringUtil.h"

TESTS(StringTests)
AFACT(ConcatStrings_ReturnsStringsConcatenatedIntoAString)
AFACT(ConcatValues_ReturnsValuesConcatenatedIntoAString)
FACTS(Contains_ReturnsTrueIfStringContainsSubstring)
FACTS(CaseInsensitiveContains_ReturnsTrueIfStringCaseInsensitiveContainsSubstring)
FACTS(ReplaceFirst_ReturnsReplacedString)
FACTS(RegexReplace_ReturnsRegexReplacedString)
FACTS(StartsWith_ReturnsTrueIfStringStartsWithSubstring)
FACTS(Split_ReturnsStringSplitOnCharacterSeparator)
FACTS(TrimWhitespace_ReturnsStringWithLeadingAndTrailingSpacesAndTabsRemoved)
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

TEST(ConcatStrings_ReturnsStringsConcatenatedIntoAString)
{
   ARE_EQUAL("", String::ConcatStrings(""));
   ARE_EQUAL("1", String::ConcatStrings("1"));
   ARE_EQUAL("12", String::ConcatStrings("1", "2"));
   ARE_EQUAL("123", String::ConcatStrings("1", "2", "3"));

   const string str1 = "str1";
   string_view str2 = "str2";
   const char* const str3 = "str3";
   ARE_EQUAL("str1str2str3", String::ConcatStrings(str1, str2, str3));
}

TEST(ConcatValues_ReturnsValuesConcatenatedIntoAString)
{
   ARE_EQUAL("", String::ConcatValues(""));
   ARE_EQUAL("1", String::ConcatValues("1"));
   ARE_EQUAL("12", String::ConcatValues("1", "2"));
   ARE_EQUAL("123", String::ConcatValues("1", "2", "3"));

   const UserType userType1(1);
   const string str = "hello";
   const UserType userType3(3);
   ARE_EQUAL("1hello3", String::ConcatValues(userType1, str, userType3));
}

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

RUN_TESTS(StringTests)
