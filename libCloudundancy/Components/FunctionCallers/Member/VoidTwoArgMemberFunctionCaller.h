#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller
{
public:
   virtual void ConstCall(
      void (ClassType::*constMemberFunction)(Arg1Type, Arg2Type) const,
      const ClassType* constClassPointer, Arg1Type arg1, Arg2Type arg2) const
   {
      (constClassPointer->*constMemberFunction)(arg1, arg2);
   }

   virtual void NonConstCall(
      void (ClassType::*nonConstMemberFunction)(Arg1Type, Arg2Type),
      ClassType* nonConstClassPointer, Arg1Type arg1, Arg2Type arg2) const
   {
      (nonConstClassPointer->*nonConstMemberFunction)(arg1, arg2);
   }

   virtual ~VoidTwoArgMemberFunctionCaller() = default;
};
