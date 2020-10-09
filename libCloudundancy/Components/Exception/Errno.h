#pragma once

class Errno
{
public:
	static const int NoSuchFileOrDirectory = 2;
	static string ToReadable(int errnoValue);
};
