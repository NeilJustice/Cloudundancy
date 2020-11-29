#include "pch.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"

TESTS(CRTWatchTests)
AFACT(DefaultConstructor_SetsFunctions)
AFACT(TmNow_ReturnsTmNow)
EVIDENCE

CRTWatch _crtWatch;
METALMOCK_NONVOID0_STATIC(chrono::time_point<chrono::system_clock>, chrono::system_clock, now)
METALMOCK_NONVOID1_STATIC(long long, chrono::system_clock, to_time_t, const chrono::system_clock::time_point&)
METALMOCK_NONVOID1_FREE(tm*, localtime, const time_t* const)

static int s_numberOfCallsToLocalTimeCallInstead;
static time_t s_dereferencedTimeTArgument;
static tm s_localTimeCallInsteadReturnValue;

STARTUP
{
   _crtWatch._call_system_clock_now = BIND_0ARG_METALMOCK_OBJECT(nowMock);
   _crtWatch._call_to_time_t = BIND_1ARG_METALMOCK_OBJECT(to_time_tMock);
   _crtWatch._call_localtime = BIND_1ARG_METALMOCK_OBJECT(localtimeMock);
}

CLEANUP
{
   s_numberOfCallsToLocalTimeCallInstead = 0;
   s_dereferencedTimeTArgument = time_t{};
   s_localTimeCallInsteadReturnValue = tm{};
}

TEST(DefaultConstructor_SetsFunctions)
{
   const CRTWatch crtWatch;
   STD_FUNCTION_TARGETS(chrono::system_clock::now, crtWatch._call_system_clock_now);
   STD_FUNCTION_TARGETS(chrono::system_clock::to_time_t, crtWatch._call_to_time_t);
#ifdef __linux__
   STD_FUNCTION_TARGETS(::localtime, crtWatch._call_localtime);
#elif _WIN32
   STD_FUNCTION_TARGETS(::_localtime64, crtWatch._call_localtime);
#endif
}

static tm* localtime_CallInstead(const time_t* timeT)
{
   ++s_numberOfCallsToLocalTimeCallInstead;
   s_dereferencedTimeTArgument = *timeT;
   return &s_localTimeCallInsteadReturnValue;
}

TEST(TmNow_ReturnsTmNow)
{
   ZenUnit::Random<tm>();

   const chrono::time_point<chrono::system_clock> nowTimePoint = chrono::system_clock::now();
   nowMock.Return(nowTimePoint);

   const time_t nowTimeT = to_time_tMock.ReturnRandom();

   localtimeMock.CallInstead(localtime_CallInstead);
   //
   const tm tmNow = _crtWatch.TmNow();
   //
   METALMOCK(nowMock.CalledOnce());
   METALMOCK(to_time_tMock.CalledOnceWith(nowTimePoint));
   ARE_EQUAL(1, s_numberOfCallsToLocalTimeCallInstead);
   ARE_EQUAL(nowTimeT, s_dereferencedTimeTArgument);
   ARE_EQUAL(s_localTimeCallInsteadReturnValue, tmNow);
}

RUN_TESTS(CRTWatchTests)

int CRTWatchTests::s_numberOfCallsToLocalTimeCallInstead;
time_t CRTWatchTests::s_dereferencedTimeTArgument;
tm CRTWatchTests::s_localTimeCallInsteadReturnValue;
