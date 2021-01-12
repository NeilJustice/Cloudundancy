#include "pch.h"
#include "libCloudundancy/UtilityComponents/Environment/EnvironmentService.h"

#if defined __linux__ || defined __APPLE__
#include <pwd.h>

TESTS(EnvironmentServiceTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(MachineName_ReturnsResultOfCallinggethostname)
AFACT(UserName_ReturnsResultOfCallinggetlogin_r)
EVIDENCE

class EnvironmentServiceSelfMocked : public Metal::Mock<EnvironmentService>
{
public:
   METALMOCK_NONVOID0_CONST(string, MachineName)
   METALMOCK_NONVOID0_CONST(string, UserName)
} _environmentServiceSelfMocked;

EnvironmentService _environmentService;
// Function Pointers
METALMOCK_NONVOID0_FREE(fs::path, current_path)
METALMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
METALMOCK_NONVOID0_FREE(uid_t, geteuid)
METALMOCK_NONVOID1_FREE(struct passwd*, getpwuid, uid_t)
// Constant Components
AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _environmentService._call_filesystem_current_path = BIND_0ARG_METALMOCK_OBJECT(current_pathMock);
   _environmentService._call_gethostname = BIND_2ARG_METALMOCK_OBJECT(gethostnameMock);
   _environmentService._call_geteuid = BIND_0ARG_METALMOCK_OBJECT(geteuidMock);
   _environmentService._call_getpwuid = BIND_1ARG_METALMOCK_OBJECT(getpwuidMock);
   // Constant Components
   _environmentService._asserter.reset(_asserterMock = new AsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   EnvironmentService environmentService;
   // Function Pointers
   STD_FUNCTION_TARGETS(gethostname, environmentService._call_gethostname);
   STD_FUNCTION_TARGETS(geteuid, environmentService._call_geteuid);
   STD_FUNCTION_TARGETS(getpwuid, environmentService._call_getpwuid);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(environmentService._asserter);
}

class gethostnameMock_CallInstead
{
private:
   size_t numberOfCalls = 0;
   char* _outLinuxMachineNameChars = nullptr;
   size_t _linuxMachineNameCharsSize = 0;
public:
   string outLinuxMachineNameCharsReturnValue;
   int returnValue = 0;

   int CallInstead(char* outLinuxMachineNameChars, size_t linuxMachineNameCharsSize)
   {
      ++numberOfCalls;
      _outLinuxMachineNameChars = outLinuxMachineNameChars;
      memcpy(outLinuxMachineNameChars, outLinuxMachineNameCharsReturnValue.c_str(), outLinuxMachineNameCharsReturnValue.size());
      _linuxMachineNameCharsSize = linuxMachineNameCharsSize;
      return returnValue;
   }

   void CalledOnceWith(size_t expectedOutLinuxMachineNameCharsSize)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(_outLinuxMachineNameChars);
      ARE_EQUAL(expectedOutLinuxMachineNameCharsSize, _linuxMachineNameCharsSize);
   }
} _gethostnameMock_CallInstead;

TEST(MachineName_ReturnsResultOfCallinggethostname)
{
   _gethostnameMock_CallInstead.outLinuxMachineNameCharsReturnValue = ZenUnit::Random<string>();
   gethostnameMock.CallInstead(std::bind(
      &gethostnameMock_CallInstead::CallInstead, &_gethostnameMock_CallInstead, placeholders::_1, placeholders::_2));
   _asserterMock->ThrowIfIntsNotEqualMock.Expect();
   //
   const string linuxMachineName = _environmentService.MachineName();
   //
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(
      0, _gethostnameMock_CallInstead.returnValue,
      "_call_gethostname(hostname, sizeof(hostname)) unexpectedly did not return 0"));
   _gethostnameMock_CallInstead.CalledOnceWith(65);
   const string expectedLinuxMachineName{};
   ARE_EQUAL(_gethostnameMock_CallInstead.outLinuxMachineNameCharsReturnValue, linuxMachineName);
}

TEST(UserName_ReturnsResultOfCallinggetlogin_r)
{
   const uid_t uidValue = geteuidMock.ReturnRandom();
   struct passwd passwdValue{};
   const string pwName = ZenUnit::Random<string>();
   passwdValue.pw_name = const_cast<char*>(pwName.c_str());
   getpwuidMock.Return(&passwdValue);
   //
   const string username = _environmentService.UserName();
   //
   METALMOCK(geteuidMock.CalledOnce());
   METALMOCK(getpwuidMock.CalledOnceWith(uidValue));
   const string expectedUsername(passwdValue.pw_name);
   ARE_EQUAL(expectedUsername, username);
}

RUN_TESTS(EnvironmentServiceTests)


#elif defined _WIN32


TESTS(EnvironmentServiceTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(MachineName_ReturnsResultOfCallingGetComputerNameA)
AFACT(UserName_ReturnsResultOfCallingGetUserNameA)
EVIDENCE

class EnvironmentServiceSelfMocked : public Metal::Mock<EnvironmentService>
{
public:
   METALMOCK_NONVOID0_CONST(string, MachineName)
   METALMOCK_NONVOID0_CONST(string, UserName)
} _environmentServiceSelfMocked;

EnvironmentService _environmentService;
// Function Pointers
METALMOCK_NONVOID0_FREE(fs::path, current_path)
METALMOCK_NONVOID2_FREE(BOOL, GetComputerNameA, LPSTR, LPDWORD)
METALMOCK_NONVOID2_FREE(BOOL, GetUserNameA, LPSTR, LPDWORD)
// Constant Components
AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _environmentService._call_filesystem_current_path = BIND_0ARG_METALMOCK_OBJECT(current_pathMock);
   _environmentService._call_GetComputerNameA = BIND_2ARG_METALMOCK_OBJECT(GetComputerNameAMock);
   _environmentService._call_GetUserNameA = BIND_2ARG_METALMOCK_OBJECT(GetUserNameAMock);
   // Constant Components
   _environmentService._asserter.reset(_asserterMock = new AsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   EnvironmentService environmentService;
   // Function Pointers
   STD_FUNCTION_TARGETS(GetComputerNameA, environmentService._call_GetComputerNameA);
   STD_FUNCTION_TARGETS(GetUserNameA, environmentService._call_GetUserNameA);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(environmentService._asserter);
}

class GetComputerNameAMock_CallInstead
{
private:
   size_t numberOfCalls = 0;
   CHAR* _outComputerNameCharsArg = nullptr;
   DWORD _computerNameCharsSizeArg = 0;
public:
   string computerNameCharsReturnValue;
   BOOL returnValue = FALSE;

   BOOL CallInstead(CHAR* outComputerNameChars, DWORD* computerNameCharsSize)
   {
      ++numberOfCalls;
      _outComputerNameCharsArg = outComputerNameChars;
      memcpy(outComputerNameChars, computerNameCharsReturnValue.c_str(), computerNameCharsReturnValue.size());
      _computerNameCharsSizeArg = *computerNameCharsSize;
      return returnValue;
   }

   void CalledOnceWith(DWORD expectedComputerNameCharsSize)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(_outComputerNameCharsArg);
      ARE_EQUAL(expectedComputerNameCharsSize, _computerNameCharsSizeArg);
   }
} _GetComputerNameAMock_CallInsteadMock;

TEST(MachineName_ReturnsResultOfCallingGetComputerNameA)
{
   _GetComputerNameAMock_CallInsteadMock.returnValue = ZenUnit::Random<BOOL>();
   _GetComputerNameAMock_CallInsteadMock.computerNameCharsReturnValue = ZenUnit::Random<string>();
   GetComputerNameAMock.CallInstead(std::bind(
      &GetComputerNameAMock_CallInstead::CallInstead, &_GetComputerNameAMock_CallInsteadMock, placeholders::_1, placeholders::_2));

   _asserterMock->ThrowIfIntsNotEqualMock.Expect();
   //
   const string windowsMachineName = _environmentService.MachineName();
   //
   METALMOCK(_GetComputerNameAMock_CallInsteadMock.CalledOnceWith(41));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(
      1, static_cast<int>(_GetComputerNameAMock_CallInsteadMock.returnValue),
      "_call_GetComputerNameA(computerNameChars, &size) unexpectedly did not return TRUE"));
   const string expectedWindowsMachineName(_GetComputerNameAMock_CallInsteadMock.computerNameCharsReturnValue);
   ARE_EQUAL(expectedWindowsMachineName, windowsMachineName);
}

class GetUserNameAMock_CallInstead
{
private:
   size_t numberOfCalls = 0;
   CHAR* _outUserNameCharsArg = nullptr;
   DWORD _usernameCharsSizeArg = 0;
public:
   string usernameCharsReturnValue;
   BOOL returnValue = FALSE;

   BOOL CallInstead(CHAR* outUserNameChars, DWORD* usernameCharsSize)
   {
      ++numberOfCalls;
      _outUserNameCharsArg = outUserNameChars;
      memcpy(outUserNameChars, usernameCharsReturnValue.c_str(), usernameCharsReturnValue.size());
      _usernameCharsSizeArg = *usernameCharsSize;
      return returnValue;
   }

   void CalledOnceWith(DWORD expectedUserNameCharsSize)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(_outUserNameCharsArg);
      ARE_EQUAL(expectedUserNameCharsSize, _usernameCharsSizeArg);
   }
} _GetUserNameAMock_CallInsteadMock;

TEST(UserName_ReturnsResultOfCallingGetUserNameA)
{
   _GetUserNameAMock_CallInsteadMock.returnValue = ZenUnit::Random<BOOL>();
   _GetUserNameAMock_CallInsteadMock.usernameCharsReturnValue = ZenUnit::Random<string>();
   GetUserNameAMock.CallInstead(std::bind(
      &GetUserNameAMock_CallInstead::CallInstead, &_GetUserNameAMock_CallInsteadMock, placeholders::_1, placeholders::_2));

   _asserterMock->ThrowIfIntsNotEqualMock.Expect();
   //
   const string windowsUserName = _environmentService.UserName();
   //
   _GetUserNameAMock_CallInsteadMock.CalledOnceWith(257);
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(
      1, static_cast<int>(_GetUserNameAMock_CallInsteadMock.returnValue),
      "_call_GetUserNameA(windowsUserNameChars, &size) unexpectedly did not return TRUE"));
   const string expectedWindowsUserName(_GetUserNameAMock_CallInsteadMock.usernameCharsReturnValue);
   ARE_EQUAL(expectedWindowsUserName, windowsUserName);
}

RUN_TESTS(EnvironmentServiceTests)

#endif
