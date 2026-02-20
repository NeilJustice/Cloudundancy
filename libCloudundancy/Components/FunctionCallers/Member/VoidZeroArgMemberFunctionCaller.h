#pragma once

namespace Utils
{
   template<typename ClassType>
   class VoidZeroArgMemberFunctionCaller
   {
   public:
      virtual ~VoidZeroArgMemberFunctionCaller() = default;

      using ConstMemberFunctionType = void (ClassType::*)() const;
      using NonConstMemberFunctionType = void (ClassType::*)();

      virtual void CallConstMemberFunction(
         const ClassType* constClassPointer,
         ConstMemberFunctionType constMemberFunction) const
      {
         (constClassPointer->*constMemberFunction)();
      }

      virtual void CallCallNonConstMemberFunctionMemberFunction(
         ClassType* nonConstClassPointer,
         NonConstMemberFunctionType nonConstMemberFunction) const
      {
         (nonConstClassPointer->*nonConstMemberFunction)();
      }
   };
}
