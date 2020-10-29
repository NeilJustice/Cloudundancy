#pragma once
#include "libCloudundancy/Components/Assertion/Asserter.h"

class AsserterMock : public Metal::Mock<Asserter>
{
public:
	METALMOCK_VOID3_CONST(ThrowIfIntsNotEqual, int, int, string_view)
	METALMOCK_VOID3_CONST(ThrowIfSizeTsNotEqual, size_t, size_t, string_view)
};
