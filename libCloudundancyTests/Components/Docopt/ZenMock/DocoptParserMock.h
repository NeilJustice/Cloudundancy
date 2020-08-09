#pragma once
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancy/Components/Time/date.h"

class DocoptParserMock : public Zen::Mock<DocoptParser>
{
public:
   using DocoptMapType = map<string, docopt::Value>;
   ZENMOCK_NONVOID2_CONST(DocoptMapType, ParseArgs, const string&, const vector<string>&)
   ZENMOCK_NONVOID2_CONST(string, GetRequiredString, const DocoptMapType&, const string&)
   ZENMOCK_NONVOID2_CONST(bool, GetRequiredBool, const DocoptMapType&, const string&)
   ZENMOCK_NONVOID4_CONST(string, GetProgramModeSpecificRequiredString, const DocoptMapType&, int, int, const string&)
   ZENMOCK_NONVOID2_CONST(bool, GetOptionalBool, const DocoptMapType&, const string&)
   ZENMOCK_NONVOID2_CONST(string, GetOptionalString, const DocoptMapType&, const string&)
};
