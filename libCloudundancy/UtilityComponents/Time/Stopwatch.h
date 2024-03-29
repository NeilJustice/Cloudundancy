#pragma once
class StopwatchTests;

namespace Utils
{
   class Stopwatch
   {
      friend class ::StopwatchTests;
   private:
      // Function Callers
      std::function<std::chrono::time_point<std::chrono::high_resolution_clock>()> _call_high_resolution_clock_now;
      // Mutable Fields
      std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
   public:
      Stopwatch();
      virtual ~Stopwatch();
      virtual void Start();
      virtual unsigned StopAndGetElapsedMilliseconds();
      virtual long long StopAndGetElapsedMicroseconds();
      virtual std::string StopAndGetElapsedSeconds();
   };
}