#pragma once
#include "libCloudundancy/Components/Assertion/Asserter.h"

class AsserterMock : public Zen::Mock<Asserter>
{
public:
	METALMOCK_VOID3_CONST(ThrowIfNotEqual, size_t, size_t, string_view)
};
