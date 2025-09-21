#pragma once

namespace Utils
{
   template<typename ClassType, typename ArgType>
   class VoidOneArgMemberFunctionCaller
   {
   public:
      VoidOneArgMemberFunctionCaller() {}

      virtual void CallConstMemberFunction(
         const ClassType* constClassPointer,
         void (ClassType::*constMemberFunction)(ArgType) const,
         ArgType arg) const
      {
         (constClassPointer->*constMemberFunction)(arg);
      }

      virtual void CallCallNonConstMemberFunctionMemberFunction(
         ClassType* nonConstClassPointer,
         void (ClassType::*nonConstMemberFunction)(ArgType),
         ArgType arg) const
      {
         (nonConstClassPointer->*nonConstMemberFunction)(arg);
      }

      virtual ~VoidOneArgMemberFunctionCaller() = default;
   };
}
