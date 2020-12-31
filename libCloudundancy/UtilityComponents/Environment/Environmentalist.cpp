#include "pch.h"
#include "libCloudundancy/UtilityComponents/Environment/Environmentalist.h"
#if defined __linux__ || defined __APPLE__
#include <pwd.h>
#endif

Environmentalist::Environmentalist() noexcept
   // Function Pointers
   : _call_filesystem_current_path(static_cast<fs::path(*)()>(fs::current_path))
#if defined __linux__
   , _call_gethostname(::gethostname)
#elif defined _WIN32
   , _call_GetComputerNameA(::GetComputerNameA)
   , _call_GetUserNameA(::GetUserNameA)
#endif
   // Constant Components
   , _asserter(make_unique<Asserter>())
{
}

string Environmentalist::MachineName() const
{
#if defined __linux__ || defined __APPLE__
   return LinuxMachineName();
#elif defined _WIN32
   return WindowsMachineName();
#endif
}

string Environmentalist::UserName() const
{
#if defined __linux__ || defined __APPLE__
   return LinuxUserName();
#elif _WIN32
   return WindowsUserName();
#endif
}

#if defined __linux__ || defined __APPLE__

string Environmentalist::LinuxMachineName() const
{
   char linuxMachineNameChars[65]{};
   const int gethostnameResult = _call_gethostname(linuxMachineNameChars, sizeof(linuxMachineNameChars));
   _asserter->ThrowIfIntsNotEqual(0, gethostnameResult,
      "_call_gethostname(hostname, sizeof(hostname)) unexpectedly did not return 0: " + to_string(gethostnameResult));
   string linuxMachineName(linuxMachineNameChars);
   return linuxMachineName;
}

string Environmentalist::LinuxUserName() const
{
   const uid_t uidValue = geteuid();
   struct passwd* const passwdValue = getpwuid(uidValue);
   release_assert(passwdValue != nullptr);
   string username(passwdValue->pw_name);
   return username;
}

#elif defined _WIN32

string Environmentalist::WindowsMachineName() const
{
   CHAR computerNameChars[41]{};
   DWORD computerNameCharsSize = sizeof(computerNameChars);
   const BOOL didGetComputerName = _call_GetComputerNameA(computerNameChars, &computerNameCharsSize);
   _asserter->ThrowIfIntsNotEqual(1, static_cast<int>(didGetComputerName),
      "_call_GetComputerNameA(computerNameChars, &size) unexpectedly did not return TRUE");
   string windowsMachineName(computerNameChars);
   return windowsMachineName;
}

string Environmentalist::WindowsUserName() const
{
   CHAR windowsUserNameChars[257]{};
   DWORD windowsUserNameCharsSize = sizeof(windowsUserNameChars);
   const BOOL didGetUserName = _call_GetUserNameA(windowsUserNameChars, &windowsUserNameCharsSize);
   _asserter->ThrowIfIntsNotEqual(1, static_cast<int>(didGetUserName),
      "_call_GetUserNameA(windowsUserNameChars, &size) unexpectedly did not return TRUE");
   string windowsUserName(windowsUserNameChars);
   return windowsUserName;
}

#endif
