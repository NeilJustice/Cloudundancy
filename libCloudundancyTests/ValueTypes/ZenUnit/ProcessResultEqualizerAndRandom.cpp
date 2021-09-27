#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/ProcessResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<Utils::ProcessResult>::AssertEqual(const Utils::ProcessResult& expectedProcessResult, const Utils::ProcessResult& actualProcessResult)
   {
      ARE_EQUAL(expectedProcessResult.processName, actualProcessResult.processName);
      ARE_EQUAL(expectedProcessResult.arguments, actualProcessResult.arguments);
      ARE_EQUAL(expectedProcessResult.exitCode, actualProcessResult.exitCode);
      ARE_EQUAL(expectedProcessResult.standardOutputAndError, actualProcessResult.standardOutputAndError);
      ARE_EQUAL(expectedProcessResult.durationInMilliseconds, actualProcessResult.durationInMilliseconds);
   }

   Utils::ProcessResult TestableRandomProcessResult(const ZenUnit::RandomGenerator* randomGenerator)
   {
      Utils::ProcessResult randomProcessResult;
      randomProcessResult.processName = randomGenerator->String();
      randomProcessResult.arguments = randomGenerator->String();
      randomProcessResult.exitCode = randomGenerator->Int();
      randomProcessResult.standardOutputAndError = randomGenerator->String();
      randomProcessResult.durationInMilliseconds = randomGenerator->Unsigned();
      return randomProcessResult;
   }

   template<>
   Utils::ProcessResult Random<Utils::ProcessResult>()
   {
      return TestableRandomProcessResult(ZenUnit::RandomGenerator::Instance());
   }
}
