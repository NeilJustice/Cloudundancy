#pragma once
struct ProcessResult;

namespace ZenUnit
{
   template<>
   struct Equalizer<ProcessResult>
   {
      static void AssertEqual(const ProcessResult& expectedProcessResult, const ProcessResult& actualProcessResult);
   };

   ProcessResult TestableRandomProcessResult(const ZenUnit::RandomGenerator* randomGenerator);
   template<>
   ProcessResult Random<ProcessResult>();
}
