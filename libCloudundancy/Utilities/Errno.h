#pragma once

class Errno
{
public:
	Errno() = delete;
	static const int NoSuchFileOrDirectory = 2;
	static string ToReadable(int errnoValue);
};
