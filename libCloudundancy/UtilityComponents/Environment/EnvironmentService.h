#pragma once

#if defined __linux__ || defined __APPLE__

class EnvironmentService
{
   friend class EnvironmentServiceTests;
private:
   // Function Pointers
   std::function<fs::path()> _call_filesystem_current_path;
   std::function<int(char*, size_t)> _call_gethostname;
   std::function<uid_t()> _call_geteuid;
   std::function<struct passwd*(uid_t)> _call_getpwuid;
   // Constant Components
   unique_ptr<const Asserter> _asserter;
public:
   EnvironmentService() noexcept;
   virtual ~EnvironmentService() = default;
   virtual string MachineName() const;
   virtual string UserName() const;
};

#elif _WIN32

class EnvironmentService
{
   friend class EnvironmentServiceTests;
private:
   // Function Pointers
   std::function<fs::path()> _call_filesystem_current_path;
   std::function<BOOL(LPSTR, LPDWORD)> _call_GetComputerNameA;
   std::function<BOOL(LPSTR, LPDWORD)> _call_GetUserNameA;
   // Constant Components
   unique_ptr<const Asserter> _asserter;
public:
   EnvironmentService() noexcept;
   virtual ~EnvironmentService() = default;
   virtual string MachineName() const;
   virtual string UserName() const;
};

#endif
