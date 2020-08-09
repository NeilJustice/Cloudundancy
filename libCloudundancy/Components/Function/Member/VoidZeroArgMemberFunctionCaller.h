#pragma once

template<typename ClassType>
class VoidZeroArgMemberFunctionCaller
{
public:
   virtual void ConstCall(
      const ClassType* classPointer, void (ClassType::*constMemberFunction)() const) const
   {
      (classPointer->*constMemberFunction)();
   }

   virtual void NonConstCall(
      ClassType* classPointer, void (ClassType::*nonConstMemberFunction)()) const
   {
      (classPointer->*nonConstMemberFunction)();
   }

   virtual ~VoidZeroArgMemberFunctionCaller() = default;
};
