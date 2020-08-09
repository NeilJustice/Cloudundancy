#pragma once

template<typename ClassType, typename ArgType>
class VoidOneArgMemberFunctionCaller
{
public:
   virtual void ConstCall(
      const ClassType* classPointer,
      void (ClassType::*constMemberFunction)(ArgType) const,
      ArgType arg) const
   {
      (classPointer->*constMemberFunction)(arg);
   }

   virtual void NonConstCall(
      ClassType* classPointer,
      void (ClassType::*nonConstMemberFunction)(ArgType),
      ArgType arg) const
   {
      (classPointer->*nonConstMemberFunction)(arg);
   }

   virtual ~VoidOneArgMemberFunctionCaller() = default;
};
