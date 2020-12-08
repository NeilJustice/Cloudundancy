#include "pch.h"
#include "libCloudundancy/UtilityComponents/Environment/Environmentalist.h"

Environmentalist::Environmentalist() noexcept
   : _call_filesystem_current_path(static_cast<fs::path(*)()>(fs::current_path))
#if defined __linux__
   , _call_gethostname(::gethostname)
#elif defined _WIN32
   , _call_GetComputerNameA(::GetComputerNameA)
   , _call_GetUserNameA(::GetUserNameA)
#endif
{
}

string Environmentalist::MachineName() const
{
#if defined __linux__
   return LinuxMachineName();
#elif defined _WIN32
   return WindowsMachineName();
#endif
}

string Environmentalist::UserName() const
{
#ifdef __linux__
   return LinuxUserName();
#elif _WIN32
   return WindowsUserName();
#endif
}

#if defined __linux__

string Environmentalist::LinuxMachineName() const
{
   char hostname[65]{};
   const int gethostnameResult = _call_gethostname(hostname, sizeof(hostname));
   release_assert(gethostnameResult == 0);
   string linuxMachineName(hostname);
   return linuxMachineName;
}

string Environmentalist::LinuxUserName() const
{
   char usernameChars[_SC_LOGIN_NAME_MAX];
   const int getloginReturnValue = getlogin_r(usernameChars, sizeof(usernameChars));
   release_assert(getloginReturnValue == 0);
   string username(usernameChars);
   return username;
}

#elif defined _WIN32

string Environmentalist::WindowsMachineName() const
{
   CHAR computerNameChars[41]{};
   DWORD size = sizeof(computerNameChars);
   const BOOL didGetComputerName = _call_GetComputerNameA(computerNameChars, &size);
   release_assert(didGetComputerName == TRUE);
   string windowsMachineName(computerNameChars);
   return windowsMachineName;
}

string Environmentalist::WindowsUserName() const
{
   CHAR windowsUserNameCharacters[257];
   DWORD size = sizeof(windowsUserNameCharacters);
   const BOOL didGetUserName = _call_GetUserNameA(windowsUserNameCharacters, &size);
   release_assert(didGetUserName == TRUE);
   string windowsUserName(windowsUserNameCharacters);
   return windowsUserName;
}

#endif
