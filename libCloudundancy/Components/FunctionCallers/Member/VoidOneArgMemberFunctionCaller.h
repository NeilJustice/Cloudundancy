#pragma once

template<typename ClassType, typename ArgType>
class VoidOneArgMemberFunctionCaller
{
public:
   virtual void CallConstMemberFunction(
      void (ClassType::*constMemberFunction)(ArgType) const,
      const ClassType* constClassPointer, ArgType arg) const
   {
      (constClassPointer->*constMemberFunction)(arg);
   }

   virtual void CallNonConstCallMemberFunction(
      void (ClassType::*nonConstMemberFunction)(ArgType),
      ClassType* nonConstClassPointer, ArgType arg) const
   {
      (nonConstClassPointer->*nonConstMemberFunction)(arg);
   }

   virtual ~VoidOneArgMemberFunctionCaller() = default;
};
