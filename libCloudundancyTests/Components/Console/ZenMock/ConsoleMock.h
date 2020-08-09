#pragma once
#include "libCloudundancy/Components/Console/Console.h"

class ConsoleMock : public Zen::Mock<Console>
{
public:
	ZENMOCK_VOID1_CONST(Write, string_view)
	ZENMOCK_VOID1_CONST(WriteLine, string_view)
   ZENMOCK_VOID2_CONST(WriteLineColor, string_view, Color)
#ifdef _WIN32
	ZENMOCK_NONVOID1_CONST(WindowsColor, SetTextColor, WindowsColor)
#endif
};
