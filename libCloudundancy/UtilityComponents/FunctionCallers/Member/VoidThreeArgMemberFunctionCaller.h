#pragma once

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgMemberFunctionCaller
   {
   public:
      virtual void ConstCall(
         const ClassType* classPointer,
         void (ClassType::*constMemberFunction)(Arg1Type, Arg2Type, Arg3Type) const,
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3) const
      {
         (classPointer->*constMemberFunction)(arg1, arg2, arg3);
      }

      virtual void NonConstCall(
         ClassType* classPointer,
         void (ClassType::*nonConstMemberFunction)(Arg1Type, Arg2Type, Arg3Type),
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3) const
      {
         (classPointer->*nonConstMemberFunction)(arg1, arg2, arg3);
      }

      virtual ~VoidThreeArgMemberFunctionCaller() = default;
   };
}
