#include "pch.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"

CRTWatch::CRTWatch()
   // Function Pointers
   : _call_system_clock_now(chrono::system_clock::now)
   , _call_to_time_t(chrono::system_clock::to_time_t)
#ifdef __linux__
   , _call_localtime(::localtime)
#elif _WIN32
   , _call_localtime64_s(::_localtime64_s)
#endif
   // Constant Components
   , _asserter(make_unique<Asserter>())
{
}

CRTWatch::~CRTWatch()
{
}

#ifdef __linux__

tm CRTWatch::TmNow() const
{
   const chrono::time_point<chrono::system_clock> nowAsTimePoint = _call_system_clock_now();
   const time_t nowAsTimeT = _call_to_time_t(nowAsTimePoint);
   const tm* const nowAsTmPointer = _call_localtime(&nowAsTimeT);
   const tm nowAsTm = *nowAsTmPointer;
   return nowAsTm;
}

#elif _WIN32

tm CRTWatch::TmNow() const
{
   const chrono::time_point<chrono::system_clock> nowAsTimePoint = _call_system_clock_now();
   const time_t nowAsTimeT = _call_to_time_t(nowAsTimePoint);
   tm nowAsTm{};
   const errno_t localtime64ReturnValue = _call_localtime64_s(&nowAsTm, &nowAsTimeT);
   _asserter->ThrowIfIntsNotEqual(0, localtime64ReturnValue, "_localtime64_s(&nowAsTm, &nowAsTimeT) unexpectedly returned non-0");
   return nowAsTm;
}

#endif
