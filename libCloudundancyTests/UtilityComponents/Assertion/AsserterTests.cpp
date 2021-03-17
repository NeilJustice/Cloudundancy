#include "pch.h"
#include "libCloudundancy/UtilityComponents/Assertion/Asserter.h"

TESTS(AsserterTests)
AFACT(ThrowIfIntsNotEqual_IntsAreEqual_DoesNotThrowException)
AFACT(ThrowIfIntsNotEqual_IntsAreNotEqual_ThrowsRuntimeError)
AFACT(ThrowIfSizeTsNotEqual_SizeTAreEqual_DoesNotThrowException)
AFACT(ThrowIfSizeTsNotEqual_SizeTAreNotEqual_ThrowsRuntimeError)
EVIDENCE

Asserter _asserter;

TEST(ThrowIfIntsNotEqual_IntsAreEqual_DoesNotThrowException)
{
	const int expected = ZenUnit::Random<int>();
	const int actual = expected;
	const string message = ZenUnit::Random<string>();
	//
	_asserter.ThrowIfIntsNotEqual(expected, actual, message);
}

TEST(ThrowIfIntsNotEqual_IntsAreNotEqual_ThrowsRuntimeError)
{
	const int expected = ZenUnit::RandomNon0<int>();
	const int actual = ZenUnit::RandomNotEqualToValue<int>(expected);
	const string message = ZenUnit::Random<string>();
	//
	const string expectedExceptionMessage = String::Concat(
		"Asserter::ThrowIfIntsNotEqual(expected, actual, message) failed due to expected != actual.\n",
		" expected=", expected, '\n', "   actual=", actual, '\n', "  message=\"", message, "\"");
	THROWS_EXCEPTION(_asserter.ThrowIfIntsNotEqual(expected, actual, message),
		runtime_error, expectedExceptionMessage);
}

TEST(ThrowIfSizeTsNotEqual_SizeTAreEqual_DoesNotThrowException)
{
	const size_t expected = ZenUnit::Random<size_t>();
	const size_t actual = expected;
	const string message = ZenUnit::Random<string>();
	//
	_asserter.ThrowIfSizeTsNotEqual(expected, actual, message);
}

TEST(ThrowIfSizeTsNotEqual_SizeTAreNotEqual_ThrowsRuntimeError)
{
	const size_t expected = ZenUnit::RandomNon0<size_t>();
	const size_t actual = expected - 1;
	const string message = ZenUnit::Random<string>();
	//
	const string expectedExceptionMessage = String::Concat(
		"Asserter::ThrowIfSizeTsNotEqual(expected, actual, message) failed due to expected != actual.\n",
		" expected=", expected, '\n', "   actual=", actual, '\n', "  message=\"", message, "\"");
	THROWS_EXCEPTION(_asserter.ThrowIfSizeTsNotEqual(expected, actual, message),
		runtime_error, expectedExceptionMessage);
}

RUN_TESTS(AsserterTests)
