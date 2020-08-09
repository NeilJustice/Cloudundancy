#include "pch.h"
#include "libCloudundancy/Components/Assertion/ReleaseAssert.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"

Stopwatch::Stopwatch()
   : _call_high_resolution_clock_now(chrono::high_resolution_clock::now)
{
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::Start()
{
   _startTime = _call_high_resolution_clock_now();
}

unsigned Stopwatch::StopAndGetElapsedMilliseconds()
{
   if (_startTime == chrono::time_point<chrono::high_resolution_clock>())
   {
      return 0;
   }
   const chrono::time_point<chrono::high_resolution_clock> stopTime = _call_high_resolution_clock_now();
   const long long elapsedMillisecondsLongLong =
      chrono::duration_cast<chrono::milliseconds>(stopTime - _startTime).count();
   release_assert(elapsedMillisecondsLongLong <= numeric_limits<unsigned>::max());
   const unsigned elapsedMilliseconds = static_cast<unsigned>(elapsedMillisecondsLongLong);
   _startTime = chrono::time_point<chrono::high_resolution_clock>();
   return elapsedMilliseconds;
}

long long Stopwatch::StopAndGetElapsedMicroseconds()
{
   if (_startTime == std::chrono::time_point<std::chrono::high_resolution_clock>())
   {
      return 0u;
   }
   const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = _call_high_resolution_clock_now();
   const std::chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
   const long long elapsedMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
   _startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
   return elapsedMicroseconds;
}

std::string Stopwatch::StopAndGetElapsedSeconds()
{
   // Example elapsedMicroseconds: 1000
   const long long elapsedMicroseconds = StopAndGetElapsedMicroseconds();

   // Example elapsedMilliseconds: 1
   const long long elapsedMilliseconds = elapsedMicroseconds / 1000;

   // Example elapsedMillisecondsMod1000: 1
   const long long elapsedMillisecondsMod1000 = elapsedMilliseconds % 1000;

   // Example elapsedSeconds: 0
   const long long elapsedSeconds = elapsedMilliseconds / 1000;

   const size_t numberOfLeadingMillisecondZeros =
      elapsedMillisecondsMod1000 < 10 ? 2 : // 3 -> 0.003
      elapsedMillisecondsMod1000 < 100 ? 1 : // 33 -> 0.033
      0; // 333 -> 0.333

   // Example leadingZeros: "00"
   const std::string leadingZeros(numberOfLeadingMillisecondZeros, '0');

   // Example elapsedSecondsWithMillisecondResolution: "0.001"
   const std::string elapsedSecondsWithMillisecondResolution =
      String::Concat(elapsedSeconds, '.', leadingZeros, elapsedMillisecondsMod1000);

   return elapsedSecondsWithMillisecondResolution;
}
