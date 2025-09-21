#include "pch.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"

TESTS(CRTWatchTests)
AFACT(DefaultConstructor_SetsFunctionPointers_NewsAsserter)
AFACT(TmNow_ReturnsTmNow)
EVIDENCE

Utils::CRTWatch _crtWatch;
// Function Pointers
METALMOCK_NONVOID0_STATIC_OR_FREE(chrono::time_point<chrono::system_clock>, _call_system_clock_now)
METALMOCK_NONVOID1_STATIC_OR_FREE(long long, _call_to_time_t, const chrono::system_clock::time_point&)
#if defined __linux__
METALMOCK_NONVOID1_STATIC_OR_FREE(tm*, localtime, const time_t* const)
#elif _WIN32
METALMOCK_NONVOID2_STATIC_OR_FREE(errno_t, _localtime64_s, tm*, const time_t*)
#endif
// Constant Components
Utils::AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _crtWatch._call_system_clock_now = BIND_0ARG_METALMOCK_OBJECT(_call_system_clock_nowMock);
   _crtWatch._call_to_time_t = BIND_1ARG_METALMOCK_OBJECT(_call_to_time_tMock);
#if defined __linux__
   _crtWatch._call_localtime = BIND_1ARG_METALMOCK_OBJECT(localtimeMock);
#elif _WIN32
   _crtWatch._call_localtime64_s = BIND_2ARG_METALMOCK_OBJECT(_localtime64_sMock);
#endif
   // Constant Components
   _crtWatch._asserter.reset(_asserterMock = new Utils::AsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_NewsAsserter)
{
   Utils::CRTWatch crtWatch;
   // Function Pointers
   STD_FUNCTION_TARGETS(chrono::system_clock::now, crtWatch._call_system_clock_now);
   STD_FUNCTION_TARGETS(chrono::system_clock::to_time_t, crtWatch._call_to_time_t);
#if defined __linux__
   STD_FUNCTION_TARGETS(localtime, crtWatch._call_localtime);
#elif _WIN32
   STD_FUNCTION_TARGETS(_localtime64_s, crtWatch._call_localtime64_s);
#endif
   // Constant Components
   DELETE_TO_ASSERT_NEWED(crtWatch._asserter);
}

#if defined __linux__

struct localtimeCallHistory
{
   int numberOfCalls = 0;
   tm returnValue;
   time_t timeTArgument = 0;

   tm* RecordCall(const time_t* timeT)
   {
      ++numberOfCalls;
      timeTArgument = *timeT;
      return &returnValue;
   }

   void AssertCalledOnceWith(const time_t& expectedTimeTArgument) const
   {
      ARE_EQUAL(1, numberOfCalls);
      ARE_EQUAL(expectedTimeTArgument, timeTArgument);
   }

} _localtimeCallHistory;

tm* localtime_CallInstead(const time_t* timeT)
{
   return _localtimeCallHistory.RecordCall(timeT);
}

TEST(TmNow_ReturnsTmNow)
{
   const chrono::time_point<chrono::system_clock> nowTimePoint = chrono::system_clock::now();
   _call_system_clock_nowMock.Return(nowTimePoint);

   const time_t nowAsTimeT = _call_to_time_tMock.ReturnRandom();

   localtimeMock.CallInstead(std::bind(&CRTWatchTests::localtime_CallInstead, this, std::placeholders::_1));
   //
   const tm tmNow = _crtWatch.TmNow();
   //
   METALMOCK(_call_system_clock_nowMock.CalledOnce());
   METALMOCK(_call_to_time_tMock.CalledOnceWith(nowTimePoint));
   _localtimeCallHistory.AssertCalledOnceWith(nowAsTimeT);
   ARE_EQUAL(_localtimeCallHistory.returnValue, tmNow);
}

#elif _WIN32

struct _localtime64_sCallHistory
{
   errno_t returnValue = 0;
   size_t numberOfCalls = 0;
   tm dereferencedOutTmArgument;
   time_t dereferencedTimeTArgument = 0;

   errno_t RecordCall(const tm* outTm, const time_t* timeT)
   {
      ++numberOfCalls;
      dereferencedOutTmArgument = *outTm;
      dereferencedTimeTArgument = *timeT;
      return returnValue;
   }

   void AssertCalledOnceWith(tm expectedDereferencedOutTmArgument, time_t expectedDereferencedTimeTArgument)
   {
      ARE_EQUAL(1, numberOfCalls);
      ARE_EQUAL(expectedDereferencedOutTmArgument, dereferencedOutTmArgument);
      ARE_EQUAL(expectedDereferencedTimeTArgument, dereferencedTimeTArgument);
   }
} _localtime64_sCallHistory;

errno_t _localtime64_sCallInstead(const tm* outTm, const time_t* timeT)
{
   return _localtime64_sCallHistory.RecordCall(outTm, timeT);
}

TEST(TmNow_ReturnsTmNow)
{
   const chrono::time_point<chrono::system_clock> nowTimePoint = chrono::system_clock::now();
   _call_system_clock_nowMock.Return(nowTimePoint);

   const time_t nowAsTimeT = _call_to_time_tMock.ReturnRandom();

   _localtime64_sCallHistory.returnValue = ZenUnit::Random<errno_t>();
   _localtime64_sMock.CallInstead(std::bind(
      &CRTWatchTests::_localtime64_sCallInstead, this, std::placeholders::_1, std::placeholders::_2));

   _asserterMock->ThrowIfIntsNotEqualMock.Expect();
   //
   const tm tmNow = _crtWatch.TmNow();
   //
   METALMOCKTHEN(_call_system_clock_nowMock.CalledOnce()).Then(
   METALMOCKTHEN(_call_to_time_tMock.CalledOnceWith(nowTimePoint))).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(
      0, _localtime64_sCallHistory.returnValue, "_localtime64_s(&nowAsTm, &nowAsTimeT) unexpectedly returned non-0")));
   _localtime64_sCallHistory.AssertCalledOnceWith(tm{}, nowAsTimeT);
}

#endif

RUN_TESTS(CRTWatchTests)
