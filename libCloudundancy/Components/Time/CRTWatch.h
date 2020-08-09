#pragma once
class CRTWatchTests;

class CRTWatch
{
   friend class ::CRTWatchTests;
private:
   function<chrono::time_point<chrono::system_clock>()> _call_system_clock_now;
   function<long long(const chrono::system_clock::time_point&)> _call_to_time_t;
   function<tm*(const time_t* const)> _call_localtime;
public:
   CRTWatch();
   virtual ~CRTWatch();
   virtual tm TmNow() const;
};
