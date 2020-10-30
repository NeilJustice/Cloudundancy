#include "pch.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"
#include "libCloudundancy/Components/Time/Watch.h"
#include "libCloudundancyTests/Components/Time/MetalMock/CRTWatchMock.h"

TESTS(WatchTests)
AFACT(DefaultConstructor_NewsCRTWatch)
FACTS(DateTimeNow_ReturnsLocalDateTimeNow)
FACTS(DateTimeNowForFileNames_ReturnsYYYYDashMMDashDDUnderscoreHHDashMM)
AFACT(GetTimeZone_ReturnTimeZoneOfExecutingProcess)
EVIDENCE

class WatchSelfMocked : public Metal::Mock<Watch>
{
public:
   METALMOCK_NONVOID0_CONST(tm, TMNow)
   METALMOCK_NONVOID1_CONST(string, GetTimeZone, const tm&)
};
unique_ptr<WatchSelfMocked> _watchSelfMocked;
CRTWatchMock* _crtWatchMock = nullptr;

STARTUP
{
   _watchSelfMocked = make_unique<WatchSelfMocked>();
   _watchSelfMocked->_crtWatch.reset(_crtWatchMock = new CRTWatchMock);
}

TEST(DefaultConstructor_NewsCRTWatch)
{
   Watch watch;
   DELETE_TO_ASSERT_NEWED(watch._crtWatch);
}

TEST2X2(DateTimeNow_ReturnsLocalDateTimeNow,
   const tm& tmNow, const string& expectedDateTimeNowPrefix,
   Tm(0, 1, 0, 0, 0, 0), "1900-01-01 12:00:00 AM ",
   Tm(1, 2, 1, 1, 1, 1), "1901-02-02 01:01:01 AM ",
   Tm(2, 3, 2, 11, 11, 11), "1902-03-03 11:11:11 AM ",
   Tm(11, 31, 99, 23, 59, 59), "1999-12-31 11:59:59 PM ",
   Tm(0, 1, 100, 0, 0, 0), "2000-01-01 12:00:00 AM ",
   Tm(1, 3, 101, 4, 5, 6), "2001-02-03 04:05:06 AM ")
{
   _watchSelfMocked->TMNowMock.Return(tmNow);
   const string timeZone = _watchSelfMocked->GetTimeZoneMock.ReturnRandom();
   //
   const string dateTimeNow = _watchSelfMocked->DateTimeNow();
   //
   METALMOCK(_watchSelfMocked->TMNowMock.CalledOnce());
   METALMOCK(_watchSelfMocked->GetTimeZoneMock.CalledOnceWith(tmNow));
   const string expectedDateTimeNow = expectedDateTimeNowPrefix + timeZone;
   ARE_EQUAL(expectedDateTimeNow, dateTimeNow);
}

TEST6X6(DateTimeNowForFileNames_ReturnsYYYYDashMMDashDDUnderscoreHHDashMM,
   const char* expectedReturnValue, int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min,
   "1900-01-01@00-00", 0, 0, 1, 0, 0,
   "1901-02-03@04-05", 1, 1, 3, 4, 5,
   "1970-01-01@00-00", 70, 0, 1, 0, 0,
   "2000-01-01@00-00", 100, 0, 1, 0, 0,
   "2038-01-01@00-00", 138, 0, 1, 0, 0,
   "9999-12-31@23-59", 8099, 11, 31, 23, 59)
{
   tm tmValue{};
   tmValue.tm_year = tm_year;
   tmValue.tm_mon = tm_mon;
   tmValue.tm_mday = tm_mday;
   tmValue.tm_hour = tm_hour;
   tmValue.tm_min = tm_min;
   tmValue.tm_sec = ZenUnit::Random<int>();
   _crtWatchMock->TmNowMock.Return(tmValue);
   //
   const string dateTimeNowMinutes = _watchSelfMocked->DateTimeNowForFileNames();
   //
   METALMOCK(_crtWatchMock->TmNowMock.CalledOnce());
   ARE_EQUAL(expectedReturnValue, dateTimeNowMinutes);
}

TEST(GetTimeZone_ReturnTimeZoneOfExecutingProcess)
{
   Watch watch;
   const tm tmNow = watch.TMNow();
   //
   const string timeZone = watch.GetTimeZone(tmNow);
   //
   char expectedTimeZoneChars[64];
   strftime(expectedTimeZoneChars, sizeof(expectedTimeZoneChars), "%Z", &tmNow);
   const string expectedTimeZone(expectedTimeZoneChars);
   ARE_EQUAL(expectedTimeZone, timeZone);
}

static constexpr tm Tm(int tmMonth, int tmMonthDay, int tmYear, int tmHour, int tmMin, int tmSec)
{
   tm tmNow{};
   tmNow.tm_sec = tmSec;
   tmNow.tm_min = tmMin;
   tmNow.tm_hour = tmHour;
   tmNow.tm_mday = tmMonthDay;
   tmNow.tm_mon = tmMonth;
   tmNow.tm_year = tmYear;
   tmNow.tm_wday = 0;
   tmNow.tm_yday = 0;
   tmNow.tm_isdst = 0;
   return tmNow;
}

RUN_TESTS(WatchTests)
