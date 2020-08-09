#pragma once
struct ProcessResult;

namespace ZenUnit
{
   template<>
   struct Equalizer<ProcessResult>
   {
      static void AssertEqual(const ProcessResult& expectedProcessResult, const ProcessResult& actualProcessResult);
   };

   template<>
   ProcessResult Random<ProcessResult>();
}
