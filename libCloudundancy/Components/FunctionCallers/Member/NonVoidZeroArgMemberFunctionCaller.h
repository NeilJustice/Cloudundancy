#pragma once

template<typename ReturnType, typename ClassType>
class NonVoidZeroArgMemberFunctionCaller
{
public:
   virtual ReturnType ConstCall(const ClassType* constClassPointer, ReturnType(ClassType::*constMemberFunction)() const) const
   {
      const ReturnType returnValue = (constClassPointer->*constMemberFunction)();
      return returnValue;
   }

   virtual ReturnType NonConstCall(ClassType* nonConstClassPointer, ReturnType(ClassType::*nonConstMemberFunction)()) const
   {
      const ReturnType returnValue = (nonConstClassPointer->*nonConstMemberFunction)();
      return returnValue;
   }

   virtual ~NonVoidZeroArgMemberFunctionCaller() = default;
};
