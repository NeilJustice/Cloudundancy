#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller
{
public:
   virtual void ConstCall(
      const ClassType* classPointer,
      void (ClassType::*constMemberFunction)(Arg1Type, Arg2Type) const,
      Arg1Type arg1, Arg2Type arg2) const
   {
      (classPointer->*constMemberFunction)(arg1, arg2);
   }

   virtual void NonConstCall(
      ClassType* classPointer,
      void (ClassType::*nonConstMemberFunction)(Arg1Type, Arg2Type),
      Arg1Type arg1, Arg2Type arg2) const
   {
      (classPointer->*nonConstMemberFunction)(arg1, arg2);
   }

   virtual ~VoidTwoArgMemberFunctionCaller() = default;
};
