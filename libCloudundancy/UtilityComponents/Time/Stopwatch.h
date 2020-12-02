#pragma once
class StopwatchTests;

class Stopwatch
{
   friend class ::StopwatchTests;
private:
   std::function<std::chrono::time_point<std::chrono::high_resolution_clock>()> _call_high_resolution_clock_now;
   std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
public:
   Stopwatch();
   virtual void Start();
   virtual unsigned StopAndGetElapsedMilliseconds();
   virtual long long StopAndGetElapsedMicroseconds();
   virtual std::string StopAndGetElapsedSeconds();
   virtual ~Stopwatch();
};
