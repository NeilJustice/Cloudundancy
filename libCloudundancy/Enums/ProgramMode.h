#pragma once

enum struct ProgramMode : unsigned char
{
   Unset,
   ExampleLinuxIniFile,
   ExampleWindowsIniFile,
   CopyFilesToMultipleFolders,
   SevenZip,
   Invalid,
   MaxValue
};

BEGIN_ENUM_STRING_ARRAY(ProgramMode)
ENUM_STRING_ARRAY_ELEMENT(Unset)
ENUM_STRING_ARRAY_ELEMENT(ExampleLinuxIniFile)
ENUM_STRING_ARRAY_ELEMENT(ExampleWindowsIniFile)
ENUM_STRING_ARRAY_ELEMENT(CopyFilesToMultipleFolders)
ENUM_STRING_ARRAY_ELEMENT(SevenZip)
ENUM_STRING_ARRAY_ELEMENT(Invalid)
ENUM_STRING_ARRAY_ELEMENT(MaxValue)
END_ENUM_STRING_ARRAY

inline ostream& operator<<(ostream& os, ProgramMode programMode)
{
   os << ENUM_AS_STRING(ProgramMode, programMode);
   return os;
}
