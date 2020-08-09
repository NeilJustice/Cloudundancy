#pragma once
#include "libCloudundancy/Components/Strings/StringCaller.h"

class StringCallerMock : public Zen::Mock<StringCaller>
{
public:
	ZENMOCK_NONVOID2_CONST(std::vector<std::string>, Split, const std::string&, char)
};
