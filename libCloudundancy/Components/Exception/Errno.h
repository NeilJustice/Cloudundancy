#pragma once

class Errno
{
public:
	static const int NoSuchFileOrDirectory = 2;
	static const int BadFileDescriptor = 9;
	static const int PermissionDenied = 13;
	static const int InvalidArgument = 22;

	static string ToReadable(int errnoValue);
};
