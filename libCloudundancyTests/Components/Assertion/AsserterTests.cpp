#include "pch.h"
#include "libCloudundancy/Components/Assertion/Asserter.h"

TESTS(AsserterTests)
AFACT(ThrowIfNotEqual_SizeTAreEqual_DoesNotThrowException)
AFACT(ThrowIfNotEqual_SizeTAreNotEqual_ThrowsRuntimeError)
EVIDENCE

Asserter _asserter;

TEST(ThrowIfNotEqual_SizeTAreEqual_DoesNotThrowException)
{
	const size_t expected = ZenUnit::Random<size_t>();
	const size_t actual = expected;
	const string message = ZenUnit::Random<string>();
	//
	_asserter.ThrowIfNotEqual(expected, actual, message);
}

TEST(ThrowIfNotEqual_SizeTAreNotEqual_ThrowsRuntimeError)
{
	const size_t expected = ZenUnit::RandomNon0<size_t>();
	const size_t actual = expected - 1;
	const string message = ZenUnit::Random<string>();
	//
	const string expectedExceptionMessage = String::Concat(
		"Asserter::ThrowIfNotEqual(expected, actual, message) failed due to expected != actual.\n",
		" expected=", expected, '\n',
		"   actual=", actual, '\n',
		"  message=\"", message, "\"");
	THROWS_EXCEPTION(_asserter.ThrowIfNotEqual(expected, actual, message),
		runtime_error, expectedExceptionMessage);
}

RUN_TESTS(AsserterTests)
