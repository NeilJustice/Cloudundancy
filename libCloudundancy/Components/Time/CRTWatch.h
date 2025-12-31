#pragma once
class CRTWatchTests;

namespace Utils
{
   class CRTWatch
   {
      friend class ::CRTWatchTests;
   private:
      // Function Pointers
      function<chrono::time_point<chrono::system_clock>()> _call_system_clock_now;
      function<long long(const chrono::system_clock::time_point&)> _call_to_time_t;
   #if defined __linux__
      function<tm* (const time_t* const)> _call_localtime;
   #elif _WIN32
      function<errno_t(tm*, const time_t*)> _call_localtime64_s;
   #endif
      // Constant Components
      unique_ptr<const Asserter> _asserter;
   public:
      CRTWatch();
      virtual ~CRTWatch();
      virtual tm TmNow() const;
   };
}
