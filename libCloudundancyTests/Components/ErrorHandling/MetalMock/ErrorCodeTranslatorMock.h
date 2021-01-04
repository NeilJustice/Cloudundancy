#pragma once
#include "libFileRevisor/Components/ErrorHandling/ErrorCodeTranslator.h"

class ErrorCodeTranslatorMock : public Metal::Mock<ErrorCodeTranslator>
{
public:
   METALMOCK_NONVOID0_CONST(int, GetErrnoValue)
   using IntStringPairType = pair<int, string>;
   METALMOCK_NONVOID0_CONST(IntStringPairType, GetErrnoWithDescription)
   METALMOCK_NONVOID1_CONST(string, GetErrnoDescription, int)
   METALMOCK_NONVOID1_CONST(string, GetSystemErrorDescription, int)

#ifdef _WIN32
   using DWORDStringPairType = pair<DWORD, string>;
   METALMOCK_NONVOID0_CONST(DWORDStringPairType, GetWindowsLastErrorWithDescription)
   METALMOCK_NONVOID1_CONST(string, GetWindowsLastErrorDescription, DWORD)
#endif
};
