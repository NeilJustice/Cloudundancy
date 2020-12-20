#pragma once

template<typename ClassType, typename ArgumentType>
class TryCatchCaller
{
public:
   virtual int TryCatchCallNonConstMemberFunction(
      ClassType* nonConstClassPointer,
      int (ClassType::*nonConstMemberFunction)(ArgumentType),
      ArgumentType argument,
      int (ClassType::*constMemberFunctionExceptionHandler)(const exception&, ArgumentType) const) const
   {
      try
      {
         const int exitCode = (nonConstClassPointer->*nonConstMemberFunction)(argument);
         return exitCode;
      }
      catch (const exception& ex)
      {
         const int exceptionHandlerExitCode = (nonConstClassPointer->*constMemberFunctionExceptionHandler)(ex, argument);
         return exceptionHandlerExitCode;
      }
   }

   virtual void TryCatchCallConstMemberFunction(
      const ClassType* constClassPointer,
      void (ClassType::*constMemberFunction)(ArgumentType) const,
      ArgumentType argument,
      void (ClassType::*constMemberFunctionExceptionHandler)(const exception&, ArgumentType) const) const
   {
      try
      {
         (constClassPointer->*constMemberFunction)(argument);
      }
      catch (const exception& ex)
      {
         (constClassPointer->*constMemberFunctionExceptionHandler)(ex, argument);
      }
   }

   virtual ~TryCatchCaller() = default;
};
