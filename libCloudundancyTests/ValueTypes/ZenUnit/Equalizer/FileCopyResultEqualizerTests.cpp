#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FileCopyResultEqualizer.h"

TESTS(FileCopyResultEqualizerTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(FileCopyResult);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileCopyResult, sourceFilePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileCopyResult, destinationFilePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileCopyResult, copySucceeded, true);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileCopyResult, numberOfBytesCopied, ZenUnit::RandomNon0<unsigned long long>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileCopyResult, durationInMilliseconds, ZenUnit::RandomNon0<unsigned long long>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileCopyResult, errorMessage, ZenUnit::Random<string>());
}

RUN_TESTS(FileCopyResultEqualizerTests)
