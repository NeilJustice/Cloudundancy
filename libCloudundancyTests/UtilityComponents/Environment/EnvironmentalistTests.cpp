#include "pch.h"
#include "libCloudundancy/UtilityComponents/Environment/Environmentalist.h"

TESTS(EnvironmentalistTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
#if defined __linux__
AFACT(Linux__MachineName_ReturnsResultOfCallingWindowsMachineName)
AFACT(Linux__UserName_ReturnsResultOfCallingWindowsUserName)
AFACT(LinuxMachineName_ReturnsResultOfCallinggethostname)
AFACT(LinuxUserName_ReturnsResultOfCallinggetlogin_r)
#elif defined _WIN32
AFACT(Windows__MachineName_ReturnsResultOfCallingWindowsMachineName)
AFACT(Windows__UserName_ReturnsResultOfCallingWindowsUserName)
AFACT(WindowsMachineName_ReturnsResultOfCallingGetComputerNameA)
AFACT(WindowsUserName_ReturnsResultOfCallingGetUserNameA)
#endif
EVIDENCE

class EnvironmentalistSelfMocked : public Metal::Mock<Environmentalist>
{
public:
#if defined __linux__
   METALMOCK_NONVOID0_CONST(string, LinuxMachineName)
   METALMOCK_NONVOID0_CONST(string, LinuxUserName)
#elif defined _WIN32
   METALMOCK_NONVOID0_CONST(string, WindowsMachineName)
   METALMOCK_NONVOID0_CONST(string, WindowsUserName)
#endif
} _environmentalistSelfMocked;

Environmentalist _environmentalist;
// Function Pointers
METALMOCK_NONVOID0_FREE(fs::path, current_path)
#if defined __linux__
METALMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
#elif defined _WIN32
METALMOCK_NONVOID2_FREE(BOOL, GetComputerNameA, LPSTR, LPDWORD)
METALMOCK_NONVOID2_FREE(BOOL, GetUserNameA, LPSTR, LPDWORD)
#endif
// Constant Components
AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _environmentalist._call_filesystem_current_path = BIND_0ARG_METALMOCK_OBJECT(current_pathMock);
#if defined __linux__
   _environmentalist._call_gethostname = BIND_2ARG_METALMOCK_OBJECT(gethostnameMock);
#elif defined _WIN32
   _environmentalist._call_GetComputerNameA = BIND_2ARG_METALMOCK_OBJECT(GetComputerNameAMock);
#endif
   // Constant Components
   _environmentalist._asserter.reset(_asserterMock = new AsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   Environmentalist environmentalist;
   // Function Pointers
#if defined __linux__
   STD_FUNCTION_TARGETS(::gethostname, environmentalist._call_gethostname);
#elif defined _WIN32
   STD_FUNCTION_TARGETS(::GetComputerNameA, environmentalist._call_GetComputerNameA);
   STD_FUNCTION_TARGETS(::GetUserNameA, environmentalist._call_GetUserNameA);
#endif
   // Constant Components
   DELETE_TO_ASSERT_NEWED(environmentalist._asserter);
}

#if defined __linux__

TEST(Linux__MachineName_ReturnsResultOfCallingWindowsMachineName)
{
   const string machineName = _environmentalistSelfMocked.LinuxMachineNameMock.ReturnRandom();
   //
   const string returnedMachineName = _environmentalistSelfMocked.MachineName();
   //
   METALMOCK(_environmentalistSelfMocked.LinuxMachineNameMock.CalledOnce());
   ARE_EQUAL(machineName, returnedMachineName);
}

TEST(Linux__UserName_ReturnsResultOfCallingWindowsUserName)
{
   const string currentUser = _environmentalistSelfMocked.LinuxUserNameMock.ReturnRandom();
   //
   const string returnedUserName = _environmentalistSelfMocked.UserName();
   //
   METALMOCK(_environmentalistSelfMocked.LinuxUserNameMock.CalledOnce());
   ARE_EQUAL(currentUser, returnedUserName);
}

TEST(LinuxMachineName_ReturnsResultOfCallinggethostname)
{

}

TEST(LinuxUserName_ReturnsResultOfCallinggetlogin_r)
{

}

#elif defined _WIN32

TEST(Windows__MachineName_ReturnsResultOfCallingWindowsMachineName)
{
   const string machineName = _environmentalistSelfMocked.WindowsMachineNameMock.ReturnRandom();
   //
   const string returnedMachineName = _environmentalistSelfMocked.MachineName();
   //
   METALMOCK(_environmentalistSelfMocked.WindowsMachineNameMock.CalledOnce());
   ARE_EQUAL(machineName, returnedMachineName);
}

TEST(Windows__UserName_ReturnsResultOfCallingWindowsUserName)
{
   const string currentUser = _environmentalistSelfMocked.WindowsUserNameMock.ReturnRandom();
   //
   const string returnedUserName = _environmentalistSelfMocked.UserName();
   //
   METALMOCK(_environmentalistSelfMocked.WindowsUserNameMock.CalledOnce());
   ARE_EQUAL(currentUser, returnedUserName);
}

class GetComputerNameAMock_CallInstead
{
private:
   size_t numberOfCalls = 0;
   CHAR* _outComputerNameCharsArg = nullptr;
   DWORD _computerNameCharsArgSize = 0;
public:
   string computerNameCharsReturnValue;
   BOOL returnValue = FALSE;

   BOOL CallInstead(CHAR* outComputerNameChars, DWORD* computerNameCharsArgSize)
   {
      ++numberOfCalls;
      _outComputerNameCharsArg = outComputerNameChars;
      memcpy(outComputerNameChars, computerNameCharsReturnValue.c_str(), computerNameCharsReturnValue.size());
      _computerNameCharsArgSize = *computerNameCharsArgSize;
      return returnValue;
   }

   void CalledOnceWith(DWORD expectedComputerNameCharsSize)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(_outComputerNameCharsArg);
      ARE_EQUAL(expectedComputerNameCharsSize, _computerNameCharsArgSize);
   }
} _GetComputerNameAMock_CallInsteadMock;

TEST(WindowsMachineName_ReturnsResultOfCallingGetComputerNameA)
{
   _GetComputerNameAMock_CallInsteadMock.returnValue = ZenUnit::Random<BOOL>();
   _GetComputerNameAMock_CallInsteadMock.computerNameCharsReturnValue = ZenUnit::Random<string>();
   GetComputerNameAMock.CallInstead(std::bind(
      &GetComputerNameAMock_CallInstead::CallInstead, &_GetComputerNameAMock_CallInsteadMock, placeholders::_1, placeholders::_2));

   _asserterMock->ThrowIfIntsNotEqualMock.Expect();
   //
   const string windowsMachineName = _environmentalist.WindowsMachineName();
   //
   METALMOCK(_GetComputerNameAMock_CallInsteadMock.CalledOnceWith(41));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(
      1, static_cast<int>(_GetComputerNameAMock_CallInsteadMock.returnValue),
      "_call_GetComputerNameA(computerNameChars, &size) unexpectedly did not return TRUE"));
   const string expectedWindowsMachineName(_GetComputerNameAMock_CallInsteadMock.computerNameCharsReturnValue);
   ARE_EQUAL(expectedWindowsMachineName, windowsMachineName);
}

TEST(WindowsUserName_ReturnsResultOfCallingGetUserNameA)
{

}

#endif

RUN_TESTS(EnvironmentalistTests)
