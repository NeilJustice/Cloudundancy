#pragma once
#include "libCloudundancy/Components/Strings/StringCaller.h"

class StringCallerMock : public Metal::Mock<StringCaller>
{
public:
	METALMOCK_NONVOID2_CONST(std::vector<std::string>, Split, const std::string&, char)
};
