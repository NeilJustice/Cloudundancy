#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FCloseDeleter.h"

TESTS(FCloseDeleterTests)
AFACT(DefaultConstructor_SetsFCloseFunctionPointer)
#if defined __linux__
AFACT(CallOperator_FILEFilenoFieldIsNot0_CallsFCloseOnFilePointerWhichReturns0_DoesNotThrowRuntimeError)
AFACT(CallOperator_FILEFilenoFieldIsNot0_CallsFCloseOnFilePointerWhichReturnsNon0_ThrowsRuntimeError)
#elif defined _WIN32
AFACT(CallOperator_FILEPlaceholderFieldIsNotNull_CallsFCloseOnFilePointerWhichReturns0_DoesNotThrowRuntimeError)
AFACT(CallOperator_FILEPlaceholderFieldIsNotNull_CallsFCloseOnFilePointerWhichReturnsNon0_ThrowsRuntimeError)
#endif
EVIDENCE

Utils::FCloseDeleter _fcloseDeleter;
// Function Pointers
METALMOCK_NONVOID1_STATIC_OR_FREE(int, _call_fclose, FILE*)

STARTUP
{
   // Function Pointers
   _fcloseDeleter._call_fclose = BIND_1ARG_METALMOCK_OBJECT(_call_fcloseMock);
}

TEST(DefaultConstructor_SetsFCloseFunctionPointer)
{
   Utils::FCloseDeleter fcloseDeleter;
   // Function Pointers
   STD_FUNCTION_TARGETS(fclose, fcloseDeleter._call_fclose);
}

#if defined __linux__

TEST(CallOperator_FILEFilenoFieldIsNot0_CallsFCloseOnFilePointerWhichReturns0_DoesNotThrowRuntimeError)
{
   _call_fcloseMock.Return(0);
   FILE* const rawFilePointer = tmpfile();
   //
   _fcloseDeleter(rawFilePointer);
   //
   METALMOCK(_call_fcloseMock.CalledOnceWith(rawFilePointer));
}

TEST(CallOperator_FILEFilenoFieldIsNot0_CallsFCloseOnFilePointerWhichReturnsNon0_ThrowsRuntimeError)
{
   const int fcloseReturnValue = ZenUnit::RandomNon0<int>();
   _call_fcloseMock.Return(fcloseReturnValue);
   FILE* const rawFilePointer = tmpfile();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues("fclose(rawFilePointer) returned ", fcloseReturnValue);
   THROWS_EXCEPTION(_fcloseDeleter(rawFilePointer),
      runtime_error, expectedExceptionMessage);
   //
   METALMOCK(_call_fcloseMock.CalledOnceWith(rawFilePointer));
}

#elif defined _WIN32

TEST(CallOperator_FILEPlaceholderFieldIsNotNull_CallsFCloseOnFilePointerWhichReturns0_DoesNotThrowRuntimeError)
{
   _call_fcloseMock.Return(0);
   FILE* tempFilePointer = nullptr;
   tmpfile_s(&tempFilePointer);
   //
   _fcloseDeleter(tempFilePointer);
   //
   METALMOCK(_call_fcloseMock.CalledOnceWith(tempFilePointer));
}

TEST(CallOperator_FILEPlaceholderFieldIsNotNull_CallsFCloseOnFilePointerWhichReturnsNon0_ThrowsRuntimeError)
{
   const int fcloseReturnValue = ZenUnit::RandomNon0<int>();
   _call_fcloseMock.Return(fcloseReturnValue);
   FILE* tempFilePointer = nullptr;
   tmpfile_s(&tempFilePointer);
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues("fclose(rawFilePointer) returned ", fcloseReturnValue);
   THROWS_EXCEPTION(_fcloseDeleter(tempFilePointer),
      runtime_error, expectedExceptionMessage);
   //
   METALMOCK(_call_fcloseMock.CalledOnceWith(tempFilePointer));
}

#endif

RUN_TESTS(FCloseDeleterTests)
