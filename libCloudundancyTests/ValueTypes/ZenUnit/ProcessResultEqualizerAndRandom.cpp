#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/ProcessResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<ProcessResult>::AssertEqual(
      const ProcessResult& expectedProcessResult, const ProcessResult& actualProcessResult)
   {
      ARE_EQUAL(expectedProcessResult.processName, actualProcessResult.processName);
      ARE_EQUAL(expectedProcessResult.arguments, actualProcessResult.arguments);
      ARE_EQUAL(expectedProcessResult.exitCode, actualProcessResult.exitCode);
      ARE_EQUAL(expectedProcessResult.standardOutputAndError, actualProcessResult.standardOutputAndError);
      ARE_EQUAL(expectedProcessResult.durationInMilliseconds, actualProcessResult.durationInMilliseconds);
   }

   ProcessResult TestableRandomProcessResult(const ZenUnit::RandomGenerator* randomGenerator)
   {
      ProcessResult randomProcessResult;
      randomProcessResult.processName = randomGenerator->String();
      randomProcessResult.arguments = randomGenerator->String();
      randomProcessResult.exitCode = randomGenerator->Int();
      randomProcessResult.standardOutputAndError = randomGenerator->String();
      randomProcessResult.durationInMilliseconds = randomGenerator->UnsignedInt();
      return randomProcessResult;
   }

   template<>
   ProcessResult Random<ProcessResult>()
   {
      return TestableRandomProcessResult(ZenUnit::RandomGenerator::Instance());
   }
}
