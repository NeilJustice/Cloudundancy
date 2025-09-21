#pragma once

namespace Utils
{
   class Stopwatch;

   class StopwatchFactory
   {
   public:
      virtual shared_ptr<Stopwatch> NewStopwatch() const;
      virtual ~StopwatchFactory() = default;
   };
}
