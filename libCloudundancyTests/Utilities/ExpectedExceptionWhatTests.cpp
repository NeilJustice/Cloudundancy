#include "pch.h"
#include "ExpectedExceptionWhat.h"
#include "libCloudundancy/Utilities/Errno.h"

TESTS(ExpectedExceptionWhatTests)
AFACT(ErrorOpeningFile_ReturnsExpectedWhat)
AFACT(ErrorCreatingFile_ReturnsExpectedWhat)
AFACT(ErrorReadingFile_ReturnsExpectedWhat)
EVIDENCE

const string FilePath = "FilePath";
const int ErrnoValue = Errno::NoSuchFileOrDirectory;

string ExpectedWhat()
{
   const string expectedWhat(FilePath + ". Reason: " + Errno::ToReadable(ErrnoValue) + ". errno=" + to_string(ErrnoValue));
	return expectedWhat;
}

TEST(ErrorOpeningFile_ReturnsExpectedWhat)
{
	ARE_EQUAL(ExpectedWhat(), ExpectedExceptionWhat::ErrorOpeningFile(FilePath, ErrnoValue));
}

TEST(ErrorCreatingFile_ReturnsExpectedWhat)
{
	ARE_EQUAL(ExpectedWhat(), ExpectedExceptionWhat::ErrorCreatingFile(FilePath, ErrnoValue));
}

TEST(ErrorReadingFile_ReturnsExpectedWhat)
{
	ARE_EQUAL(ExpectedWhat(), ExpectedExceptionWhat::ErrorReadingFile(FilePath, ErrnoValue));
}

RUN_TESTS(ExpectedExceptionWhatTests)
