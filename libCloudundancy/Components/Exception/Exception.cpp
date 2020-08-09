#include "pch.h"
#include "libCloudundancy/Components/Exception/Exception.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"
#include "libCloudundancy/Components/Types/Type.h"

string Exception::GetExceptionClassNameAndMessage(const exception* ex)
{
   const string* exceptionTypeName = Type::GetName(*ex);
   const string exceptionMessage = ex->what();
   const string exceptionClassNameAndMessage = String::Concat(*exceptionTypeName, ": ", exceptionMessage);
	return exceptionClassNameAndMessage;
}
