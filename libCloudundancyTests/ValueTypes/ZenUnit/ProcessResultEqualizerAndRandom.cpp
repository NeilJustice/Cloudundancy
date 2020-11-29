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
      ARE_EQUAL(expectedProcessResult.milliseconds, actualProcessResult.milliseconds);
   }

   template<>
   ProcessResult Random<ProcessResult>()
   {
      ProcessResult randomProcessResult;
      randomProcessResult.processName = ZenUnit::Random<string>();
      randomProcessResult.arguments = ZenUnit::Random<string>();
      randomProcessResult.exitCode = ZenUnit::Random<int>();
      randomProcessResult.standardOutputAndError = ZenUnit::Random<string>();
      randomProcessResult.milliseconds = ZenUnit::Random<unsigned>();
      return randomProcessResult;
   }
}
