#pragma once

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename ArgType>
   class NonVoidOneArgMemberFunctionCaller
   {
   public:
      virtual ReturnType CallConstMemberFunction(
         const ClassType* constClassPointer,
         ReturnType(ClassType::* constMemberFunction)(ArgType) const,
         ArgType arg) const
      {
         ReturnType returnValue = (constClassPointer->*constMemberFunction)(arg);
         return returnValue;
      }

      virtual ReturnType CallNonConstMemberFunction(
         ClassType* nonConstClassPointer,
         ReturnType(ClassType::*nonConstMemberFunction)(ArgType),
         ArgType arg) const
      {
         ReturnType returnValue = (nonConstClassPointer->*nonConstMemberFunction)(arg);
         return returnValue;
      }

      virtual ~NonVoidOneArgMemberFunctionCaller() = default;
   };
}
