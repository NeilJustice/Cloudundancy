#include "pch.h"
#include "libCloudundancy/Utilities/Errno.h"
#include "libCloudundancyTests/Utilities/ExpectedExceptionMessage.h"

TESTS(ExpectedExceptionMessageTests)
AFACT(ErrorOpeningFile_ReturnsExpectedExceptionMessage)
AFACT(ErrorCreatingFile_ReturnsExpectedExceptionMessage)
AFACT(ErrorReadingFile_ReturnsExpectedExceptionMessage)
EVIDENCE

const string _filePath = ZenUnit::Random<string>();
const int ErrnoValue = Errno::NoSuchFileOrDirectory;

string ExpectedExceptionMessage()
{
   const string expectedExceptionMessage(
		_filePath + ". Reason: " + Errno::ToReadable(ErrnoValue) + ". errno=" + to_string(ErrnoValue));
	return expectedExceptionMessage;
}

TEST(ErrorOpeningFile_ReturnsExpectedExceptionMessage)
{
	ARE_EQUAL(ExpectedExceptionMessage(), ExpectedExceptionMessage::ErrorOpeningFile(_filePath, ErrnoValue));
}

TEST(ErrorCreatingFile_ReturnsExpectedExceptionMessage)
{
	ARE_EQUAL(ExpectedExceptionMessage(), ExpectedExceptionMessage::ErrorCreatingFile(_filePath, ErrnoValue));
}

TEST(ErrorReadingFile_ReturnsExpectedExceptionMessage)
{
	ARE_EQUAL(ExpectedExceptionMessage(), ExpectedExceptionMessage::ErrorReadingFile(_filePath, ErrnoValue));
}

RUN_TESTS(ExpectedExceptionMessageTests)
