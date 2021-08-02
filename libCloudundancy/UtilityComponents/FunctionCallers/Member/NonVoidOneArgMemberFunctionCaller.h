#pragma once

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename ArgType>
   class NonVoidOneArgMemberFunctionCaller
   {
   public:
      virtual ReturnType CallConstMemberFunction(
         ReturnType(ClassType::* constMemberFunction)(ArgType) const,
         const ClassType* constClassPointer, ArgType arg) const
      {
         ReturnType returnValue = (constClassPointer->*constMemberFunction)(arg);
         return returnValue;
      }

      virtual ReturnType CallNonConstMemberFunction(
         ReturnType(ClassType::*nonConstMemberFunction)(ArgType),
         ClassType* nonConstClassPointer, ArgType arg) const
      {
         ReturnType returnValue = (nonConstClassPointer->*nonConstMemberFunction)(arg);
         return returnValue;
      }

      virtual ~NonVoidOneArgMemberFunctionCaller() = default;
   };
}
