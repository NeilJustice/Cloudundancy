#pragma once

class Exception
{
public:
	Exception() = delete;
	static string GetExceptionClassNameAndMessage(const exception* ex);
};
