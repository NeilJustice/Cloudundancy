#include "pch.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"

TESTS(StopwatchTests)
AFACT(Ctor_SetsNowFunction)
AFACT(Start_SetsStartTimeToNow)
AFACT(StopAndGetElapsedMilliseconds_StartNotPreviouslyCalled_Returns0)
AFACT(StopAndGetElapsedMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
AFACT(StopAndGetElapsedMicroseconds_StartNotPreviouslyCalled_Returns0)
AFACT(StopAndGetElapsedMicroseconds_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
FACTS(StopAndGetElapsedSeconds_StartPreviouslyCalled_SetsStartTimeBackToDefault_ReturnsElapsedSecondsWithMillisecondResolution)
EVIDENCE

Stopwatch _stopwatch;
ZENMOCK_NONVOID0_STATIC(chrono::time_point<chrono::high_resolution_clock>, chrono::high_resolution_clock, now)

STARTUP
{
   _stopwatch._call_high_resolution_clock_now = BIND_0ARG_ZENMOCK_OBJECT(nowMock);
}

TEST(Ctor_SetsNowFunction)
{
   const Stopwatch stopwatch;
   STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch._call_high_resolution_clock_now);
   ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), stopwatch._startTime);
}

TEST(Start_SetsStartTimeToNow)
{
   chrono::time_point<chrono::high_resolution_clock> nonDefaultTimePoint = chrono::high_resolution_clock::now();
   nowMock.Return(nonDefaultTimePoint);
   //
   _stopwatch.Start();
   //
   nowMock.CalledOnce();
   ARE_EQUAL(nonDefaultTimePoint, _stopwatch._startTime);
}

TEST(StopAndGetElapsedMilliseconds_StartNotPreviouslyCalled_Returns0)
{
   ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMilliseconds());
   ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMilliseconds());
}

TEST(StopAndGetElapsedMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
{
   chrono::time_point<chrono::high_resolution_clock> startTime;
   startTime += chrono::milliseconds(100);
   const chrono::time_point<chrono::high_resolution_clock> stopTime = startTime + chrono::milliseconds(1000);
   nowMock.Return(stopTime);
   _stopwatch._startTime = startTime;
   //
   const long long elapsedMilliseconds = _stopwatch.StopAndGetElapsedMilliseconds();
   //
   ZENMOCK(nowMock.CalledOnce());
   ARE_EQUAL(1000ll, elapsedMilliseconds);
}

TEST(StopAndGetElapsedMicroseconds_StartNotPreviouslyCalled_Returns0)
{
   ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMicroseconds());
   ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMicroseconds());
}

TEST(StopAndGetElapsedMicroseconds_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
{
   chrono::time_point<chrono::high_resolution_clock> startDateTime;
   startDateTime += chrono::milliseconds(ZenUnit::Random<unsigned>());
   const unsigned randomMicrosecondDuration = ZenUnit::Random<unsigned>();
   const chrono::time_point<chrono::high_resolution_clock> stopTime = startDateTime + chrono::microseconds(randomMicrosecondDuration);
   nowMock.Return(stopTime);
   _stopwatch._startTime = startDateTime;
   //
   const long long elapsedMicroseconds = _stopwatch.StopAndGetElapsedMicroseconds();
   //
   ZENMOCK(nowMock.CalledOnce());
   ARE_EQUAL(randomMicrosecondDuration, elapsedMicroseconds);
}

TEST2X2(StopAndGetElapsedSeconds_StartPreviouslyCalled_SetsStartTimeBackToDefault_ReturnsElapsedSecondsWithMillisecondResolution,
   long long elapsedMilliseconds, const string& expectedReturnValue,
   0, "0.000",
   1, "0.001",
   9, "0.009",
   10, "0.010",
   11, "0.011",
   99, "0.099",
   100, "0.100",
   101, "0.101",
   999, "0.999",
   1000, "1.000",
   1001, "1.001",
   1099, "1.099",
   1100, "1.100",
   1101, "1.101",
   1999, "1.999",
   10000, "10.000",
   100000, "100.000",
   1234567, "1234.567")
{
   chrono::time_point<chrono::high_resolution_clock> startTime;
   const int random1To3MicrosecondOffsetFromDefaultStartTimeValue = ZenUnit::RandomBetween<int>(1, 3);
   startTime += chrono::microseconds(random1To3MicrosecondOffsetFromDefaultStartTimeValue);
   _stopwatch._startTime = startTime;

   const long long elapsedMicroseconds = elapsedMilliseconds * 1000;
   const chrono::time_point<chrono::high_resolution_clock>
      stopTimeThatIsElapsedMicrosecondsAheadOfStartTime = startTime + chrono::microseconds(elapsedMicroseconds);
   nowMock.Return(stopTimeThatIsElapsedMicrosecondsAheadOfStartTime);
   //
   const string elapsedSeconds = _stopwatch.StopAndGetElapsedSeconds();
   //
   ZENMOCK(nowMock.CalledOnce());
   ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), _stopwatch._startTime);
   ARE_EQUAL(expectedReturnValue, elapsedSeconds);
}

RUN_TESTS(StopwatchTests)
