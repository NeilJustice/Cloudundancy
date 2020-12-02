#include "pch.h"
#include "libCloudundancy/StaticUtilities/Type.h"
#include "libCloudundancy/StaticUtilities/Exception.h"

string Exception::GetExceptionClassNameAndMessage(const exception* ex)
{
   const string* exceptionTypeName = Type::GetName(*ex);
   const string exceptionMessage = ex->what();
   const string exceptionClassNameAndMessage = String::Concat(*exceptionTypeName, ": ", exceptionMessage);
	return exceptionClassNameAndMessage;
}
