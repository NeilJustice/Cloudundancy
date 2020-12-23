#pragma once

class Environmentalist
{
   friend class EnvironmentalistTests;
private:
   // Function Pointers
   std::function<fs::path()> _call_filesystem_current_path;
#if defined __linux__
   std::function<int(char*, size_t)> _call_gethostname;
#elif defined _WIN32
   std::function<BOOL(LPSTR, LPDWORD)> _call_GetComputerNameA;
   std::function<BOOL(LPSTR, LPDWORD)> _call_GetUserNameA;
#endif
   // Constant Components
   unique_ptr<const Asserter> _asserter;
public:
   Environmentalist() noexcept;
   virtual ~Environmentalist() = default;
   virtual string MachineName() const;
   virtual string UserName() const;
private:
#if defined __linux__
   virtual string LinuxMachineName() const;
   virtual string LinuxUserName() const;
#elif defined _WIN32
   virtual string WindowsMachineName() const;
   virtual string WindowsUserName() const;
#endif
};
