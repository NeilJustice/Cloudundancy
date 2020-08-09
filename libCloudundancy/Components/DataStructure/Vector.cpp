#include "pch.h"
#include "libCloudundancy/Components/Assertion/ReleaseAssert.h"
#include "libCloudundancy/Components/DataStructure/Vector.h"

vector<string> Vector::ArgcArgvToStringVector(int argc, char** argv)
{
   release_assert(argc >= 1);
   release_assert(argv != nullptr);
   vector<string> stringArgs;
   stringArgs.reserve(static_cast<size_t>(argc));
   std::for_each(argv, argv + argc, [&](char* arg)
   {
      stringArgs.emplace_back(arg);
   });
	return stringArgs;
}
