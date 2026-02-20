#pragma once
#include "libCloudundancy/Components/Docopt/DocoptParser.h"

class DocoptParserMock : public Metal::Mock<DocoptParser>
{
public:
   using DocoptMapType = map<string, docopt::value>;

   METALMOCK_NONVOID2_CONST(bool, DocoptArgsAreForProgramMode,
      const DocoptMapType&,
      const string&)

   METALMOCK_NONVOID3_CONST(DocoptMapType, ParseArgs,
      const string&,
      const vector<string>&,
      bool)

   METALMOCK_NONVOID2_CONST(string, GetRequiredString,
      const DocoptMapType&, const string&)

   METALMOCK_NONVOID2_CONST(bool, GetRequiredBool,
      const DocoptMapType&, const string&)

   METALMOCK_NONVOID4_CONST(string, GetProgramModeSpecificRequiredString,
      const DocoptMapType&, unsigned, unsigned, const string&)

   METALMOCK_NONVOID2_CONST(bool, GetOptionalBool,
      const DocoptMapType&, const string&)

   METALMOCK_NONVOID2_CONST(string, GetOptionalString,
      const DocoptMapType&, const string&)

   METALMOCK_NONVOID3_CONST(string, GetOptionalStringWithDefaultValue,
      const DocoptMapType&, string_view, string_view)

   METALMOCK_NONVOID2_CONST(size_t, GetRequiredSizeT,
      const DocoptMapType&, const string&)
};
