#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCaller
{
public:
   virtual void ConstCall(
      void (ClassType::*constMemberFunction)(Arg1Type, Arg2Type, Arg3Type) const,
      const ClassType* classPointer, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
   {
      (classPointer->*constMemberFunction)(arg1, arg2, arg3);
   }

   virtual void NonConstCall(
      void (ClassType::*nonConstMemberFunction)(Arg1Type, Arg2Type, Arg3Type),
      ClassType* classPointer, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
   {
      (classPointer->*nonConstMemberFunction)(arg1, arg2, arg3);
   }

   virtual ~VoidThreeArgMemberFunctionCaller() = default;
};
