#include "pch.h"
#include "libCloudundancy/UtilityComponents/Environment/EnvironmentService.h"

namespace Utils
{
#if defined __linux__
   EnvironmentService::EnvironmentService() noexcept
      // Function Pointers
      : _call_filesystem_current_path(static_cast<fs::path(*)()>(fs::current_path))
      , _call_gethostname(gethostname)
      , _call_geteuid(geteuid)
      , _call_getpwuid(getpwuid)
      // Constant Components
      , _asserter(make_unique<Asserter>())
   {
   }

   string EnvironmentService::MachineName() const
   {
      char linuxMachineNameChars[65]{};
      const int gethostnameResult = _call_gethostname(linuxMachineNameChars, sizeof(linuxMachineNameChars));
      _asserter->ThrowIfIntsNotEqual(0, gethostnameResult,
         "_call_gethostname(hostname, sizeof(hostname)) unexpectedly did not return 0");
      string linuxMachineName(linuxMachineNameChars);
      return linuxMachineName;
   }

   string EnvironmentService::UserName() const
   {
      const uid_t uidValue = _call_geteuid();
      const struct passwd* const passwdValue = _call_getpwuid(uidValue);
      string username(passwdValue->pw_name);
      return username;
   }

#elif defined _WIN32

   EnvironmentService::EnvironmentService() noexcept
      // Function Pointers
      : _call_filesystem_current_path(static_cast<fs::path(*)()>(fs::current_path))
      , _call_GetComputerNameA(GetComputerNameA)
      , _call_GetUserNameA(GetUserNameA)
      // Constant Components
      , _asserter(make_unique<Asserter>())
   {
   }

   string EnvironmentService::MachineName() const
   {
      CHAR computerNameChars[41]{};
      DWORD computerNameCharsSize = sizeof(computerNameChars);
      const BOOL didGetComputerName = _call_GetComputerNameA(computerNameChars, &computerNameCharsSize);
      _asserter->ThrowIfIntsNotEqual(1, static_cast<int>(didGetComputerName),
         "_call_GetComputerNameA(computerNameChars, &size) unexpectedly did not return TRUE");
      string windowsMachineName(computerNameChars);
      return windowsMachineName;
   }

   string EnvironmentService::UserName() const
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
}
