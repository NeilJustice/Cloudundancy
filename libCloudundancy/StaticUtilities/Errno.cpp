#include "pch.h"
#include "libCloudundancy/StaticUtilities/Errno.h"

string Errno::ToReadable(int errnoValue)
{
	const char* const errnoDescriptionChars = strerror(errnoValue);
   const string errnoDescription(errnoDescriptionChars);
	return errnoDescription;
}
