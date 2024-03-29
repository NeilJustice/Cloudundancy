#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/tmZenUnitEqualizerAndRandom.h"

TESTS(tmZenUnitEqualizerAndRandomTests)
AFACT(tmEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
AFACT(TestableRandomtm_ReturnsTmWithAllRandomFields)
AFACT(ZenUnitRandomtm_ReturnsResultOfCallingTestableRandomtm)
EVIDENCE

TEST(tmEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(tm);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_sec, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_min, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_hour, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_mday, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_mon, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_year, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_wday, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_yday, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(tm, tm_isdst, ZenUnit::RandomNon0<int>());

   tm expectedTm{};
   tm actualTm{};
   ZenUnit::Equalizer<tm>::AssertEqual(expectedTm, actualTm); // Function coverage for Cppcheck
}

TEST(TestableRandomtm_ReturnsTmWithAllRandomFields)
{
   const int tm_sec = ZenUnit::Random<int>();
   const int tm_min = ZenUnit::Random<int>();
   const int tm_hour = ZenUnit::Random<int>();
   const int tm_mday = ZenUnit::Random<int>();
   const int tm_mon = ZenUnit::Random<int>();
   const int tm_year = ZenUnit::Random<int>();
   const int tm_wday = ZenUnit::Random<int>();
   const int tm_yday = ZenUnit::Random<int>();
   const int tm_isdst = ZenUnit::Random<int>();
   ZenUnit::RandomGeneratorMock randomGeneratorMock;
   randomGeneratorMock.IntMock.ReturnValues(
      tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst);
   //
   const tm randomTm = TestableRandomtm(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.IntMock.CalledNTimes(9));
   tm expectedRandomTm;
   expectedRandomTm.tm_sec = tm_sec;
   expectedRandomTm.tm_min = tm_min;
   expectedRandomTm.tm_hour = tm_hour;
   expectedRandomTm.tm_mday = tm_mday;
   expectedRandomTm.tm_mon = tm_mon;
   expectedRandomTm.tm_year = tm_year;
   expectedRandomTm.tm_wday = tm_wday;
   expectedRandomTm.tm_yday = tm_yday;
   expectedRandomTm.tm_isdst = tm_isdst;
   ARE_EQUAL(expectedRandomTm, randomTm);
}

TEST(ZenUnitRandomtm_ReturnsResultOfCallingTestableRandomtm)
{
   ZenUnit::Random<tm>();
}

RUN_TESTS(tmZenUnitEqualizerAndRandomTests)
