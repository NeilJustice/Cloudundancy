#pragma once

template<typename ClassType, typename ArgumentType>
class TryCatchCaller
{
public:
   virtual int TryCatchCall(
      ClassType* classPointer,
      int (ClassType::*memberFunction)(ArgumentType),
      ArgumentType argument,
      int (ClassType::*memberExceptionHandlerFunction)(const exception&, ArgumentType)) const
   {
      try
      {
         const int exitCode = (classPointer->*memberFunction)(argument);
         return exitCode;
      }
      catch (const exception& ex)
      {
         const int exceptionHandlerExitCode = (classPointer->*memberExceptionHandlerFunction)(ex, argument);
         return exceptionHandlerExitCode;
      }
   }

   virtual ~TryCatchCaller() = default;
};
