#include "pch.h"
#include "libCloudundancy/Components/Environment/Environmentalist.h"

TESTS(EnvironmentalistTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
#if defined __linux__
AFACT(MachineName_Linux_ReturnsResultOfCallingWindowsMachineName)
AFACT(UserName_Linux_ReturnsResultOfCallingWindowsUserName)
#elif defined _WIN32
AFACT(MachineName_Windows_ReturnsResultOfCallingWindowsMachineName)
AFACT(UserName_Windows_ReturnsResultOfCallingWindowsUserName)
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
METALMOCK_NONVOID0_FREE(fs::path, current_path)
#if defined __linux__
METALMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
#elif defined _WIN32
METALMOCK_NONVOID2_FREE(BOOL, GetComputerNameA, LPSTR, LPDWORD)
METALMOCK_NONVOID2_FREE(BOOL, GetUserNameA, LPSTR, LPDWORD)
#endif

STARTUP
{
   _environmentalist._call_filesystem_current_path = BIND_0ARG_METALMOCK_OBJECT(current_pathMock);
#if defined __linux__
   _environmentalist._call_gethostname = BIND_2ARG_METALMOCK_OBJECT(gethostnameMock);
#elif defined _WIN32
   _environmentalist._call_GetComputerNameA = BIND_2ARG_METALMOCK_OBJECT(GetComputerNameAMock);
#endif
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   Environmentalist environmentalist;
#if defined __linux__
   STD_FUNCTION_TARGETS(::gethostname, environmentalist._call_gethostname);
#elif defined _WIN32
   STD_FUNCTION_TARGETS(::GetComputerNameA, environmentalist._call_GetComputerNameA);
   STD_FUNCTION_TARGETS(::GetUserNameA, environmentalist._call_GetUserNameA);
#endif
}

#if defined __linux__

TEST(MachineName_Linux_ReturnsResultOfCallingWindowsMachineName)
{
   const string machineName = _environmentalistSelfMocked.LinuxMachineNameMock.ReturnRandom();
   //
   const string returnedMachineName = _environmentalistSelfMocked.MachineName();
   //
   METALMOCK(_environmentalistSelfMocked.LinuxMachineNameMock.CalledOnce());
   ARE_EQUAL(machineName, returnedMachineName);
}

TEST(UserName_Linux_ReturnsResultOfCallingWindowsUserName)
{
   const string currentUser = _environmentalistSelfMocked.LinuxUserNameMock.ReturnRandom();
   //
   const string returnedUserName = _environmentalistSelfMocked.UserName();
   //
   METALMOCK(_environmentalistSelfMocked.LinuxUserNameMock.CalledOnce());
   ARE_EQUAL(currentUser, returnedUserName);
}

#elif defined _WIN32

TEST(MachineName_Windows_ReturnsResultOfCallingWindowsMachineName)
{
   const string machineName = _environmentalistSelfMocked.WindowsMachineNameMock.ReturnRandom();
   //
   const string returnedMachineName = _environmentalistSelfMocked.MachineName();
   //
   METALMOCK(_environmentalistSelfMocked.WindowsMachineNameMock.CalledOnce());
   ARE_EQUAL(machineName, returnedMachineName);
}

TEST(UserName_Windows_ReturnsResultOfCallingWindowsUserName)
{
   const string currentUser = _environmentalistSelfMocked.WindowsUserNameMock.ReturnRandom();
   //
   const string returnedUserName = _environmentalistSelfMocked.UserName();
   //
   METALMOCK(_environmentalistSelfMocked.WindowsUserNameMock.CalledOnce());
   ARE_EQUAL(currentUser, returnedUserName);
}

#endif

RUN_TESTS(EnvironmentalistTests)
