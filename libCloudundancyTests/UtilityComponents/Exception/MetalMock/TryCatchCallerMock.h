#pragma once
#include "libCloudundancy/UtilityComponents/Exception/TryCatchCaller.h"

template<typename ClassType, typename ArgumentType>
class TryCatchCallerMock : public Metal::Mock<TryCatchCaller<ClassType, ArgumentType>>
{
public:
   using NonConstMemberFunctionType = int (ClassType::*)(ArgumentType);
   using IntReturningExceptionHandlerType = int (ClassType::*)(const exception&, ArgumentType) const;
   METALMOCK_NONVOID4_CONST(int, TryCatchCallNonConstMemberFunction,
      ClassType*,
      NonConstMemberFunctionType,
      ArgumentType,
      IntReturningExceptionHandlerType)

   using ConstMemberFunctionType = void (ClassType::*)(ArgumentType) const;
   using VoidExceptionHandlerType = void (ClassType::*)(const exception&, ArgumentType) const;
   METALMOCK_VOID4_CONST(TryCatchCallConstMemberFunction,
      const ClassType*,
      ConstMemberFunctionType,
      ArgumentType,
      VoidExceptionHandlerType)
};
