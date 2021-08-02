#pragma once
#include "libCloudundancy/UtilityComponents/Console/Console.h"

namespace Utils
{
   class ConsoleMock : public Metal::Mock<Console>
   {
   public:
      METALMOCK_VOID1_CONST(Write, string_view)
      METALMOCK_VOID1_CONST(WriteLine, string_view)
      METALMOCK_VOID1_CONST(WriteLines, const vector<string>&)
      METALMOCK_VOID2_CONST(WriteLineIf, bool, string_view)
      METALMOCK_VOID2_CONST(WriteLineAndExit, string_view, int)
      METALMOCK_VOID2_CONST(WriteLineColor, string_view, Color)
   };
}