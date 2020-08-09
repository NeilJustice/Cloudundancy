#pragma once
#include "libCloudundancy/Components/Exception/TryCatchCaller.h"

template<typename ClassType, typename ArgumentType>
class TryCatchCallerMock : public Zen::Mock<TryCatchCaller<ClassType, ArgumentType>>
{
public:
   using MemberFunctionType = int (ClassType::*)(ArgumentType);
   using ExceptionHandlerType = int (ClassType::*)(const exception&, ArgumentType);
   ZENMOCK_NONVOID4_CONST(int, TryCatchCall, ClassType*, MemberFunctionType, ArgumentType, ExceptionHandlerType)
};
