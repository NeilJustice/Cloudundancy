#include "pch.h"
#include "libCloudundancy/Components/Exception/Errno.h"

string Errno::ToReadable(int errnoValue)
{
	const char* const errnoDescriptionChars = strerror(errnoValue);
   const string errnoDescription(errnoDescriptionChars);
	return errnoDescription;
}
