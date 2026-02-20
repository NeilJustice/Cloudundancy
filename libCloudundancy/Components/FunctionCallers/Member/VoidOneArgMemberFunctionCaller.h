#pragma once

namespace Utils
{
   template<typename ClassType, typename ArgType>
   class VoidOneArgMemberFunctionCaller
   {
   public:
      virtual ~VoidOneArgMemberFunctionCaller() = default;
      using ConstMemberFunctionType = void (ClassType::*)(ArgType) const;
      using NonConstMemberFunctionType = void (ClassType::*)(ArgType);

      virtual void CallConstMemberFunction(
         const ClassType* constClassPointer,
         ConstMemberFunctionType constMemberFunction,
         ArgType arg) const
      {
         (constClassPointer->*constMemberFunction)(arg);
      }

      virtual void CallCallNonConstMemberFunctionMemberFunction(
         ClassType* nonConstClassPointer,
         NonConstMemberFunctionType nonConstMemberFunction,
         ArgType arg) const
      {
         (nonConstClassPointer->*nonConstMemberFunction)(arg);
      }
   };
}
