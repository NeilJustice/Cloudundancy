#pragma once

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgMemberFunctionCaller
   {
   public:
      virtual ReturnType CallConstMemberFunction(
         const ClassType* classPointer,
         ReturnType(ClassType::*constMemberFunction)(Arg1Type, Arg2Type) const,
         Arg1Type arg1,
         Arg2Type arg2) const
      {
         ReturnType returnValue = (classPointer->*constMemberFunction)(arg1, arg2);
         return returnValue;
      }

      virtual ReturnType CallNonConstMemberFunction(
         ClassType* classPointer,
         ReturnType(ClassType::*nonConstMemberFunction)(Arg1Type, Arg2Type),
         Arg1Type arg1,
         Arg2Type arg2) const
      {
         ReturnType returnValue = (classPointer->*nonConstMemberFunction)(arg1, arg2);
         return returnValue;
      }

      virtual ~NonVoidTwoArgMemberFunctionCaller() = default;
   };
}