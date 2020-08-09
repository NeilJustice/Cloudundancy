#include "pch.h"
#include "libCloudundancy/Components/Strings/StringCaller.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"

vector<string> StringCaller::Split(const string& str, char separator) const
{
   const vector<string> splitString = String::Split(str, separator);
   return splitString;
}

StringCaller::~StringCaller()
{
}
