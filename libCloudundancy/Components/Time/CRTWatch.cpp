#include "pch.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"

CRTWatch::CRTWatch()
   : _call_system_clock_now(chrono::system_clock::now)
   , _call_to_time_t(chrono::system_clock::to_time_t)
#ifdef __linux__
   , _call_localtime(::localtime)
#elif _WIN32
   , _call_localtime(::_localtime64)
#endif
{
}

CRTWatch::~CRTWatch()
{
}

tm CRTWatch::TmNow() const
{
   const chrono::time_point<chrono::system_clock> nowTimePoint = _call_system_clock_now();
   const time_t nowTimeT = _call_to_time_t(nowTimePoint);
   const tm* const nowTmPointer = _call_localtime(&nowTimeT);
   const tm nowTm = *nowTmPointer;
   return nowTm;
}
