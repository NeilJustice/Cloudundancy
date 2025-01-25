#include "pch.h"
#include "libCloudundancy/StaticUtilities/GetLinuxErrno.h"

#if defined __linux__
int* GetLinuxErrno()
{
   return &errno;
}
#endif

