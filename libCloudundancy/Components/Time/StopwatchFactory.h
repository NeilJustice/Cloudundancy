#pragma once

namespace Utils
{
   class Stopwatch;

   class StopwatchFactory
   {
   public:
      virtual ~StopwatchFactory() = default;

      virtual shared_ptr<Stopwatch> NewStopwatch() const;
   };
}
