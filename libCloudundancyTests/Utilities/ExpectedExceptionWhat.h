#pragma once
#include "libCloudundancy/Utilities/Errno.h"

struct ExpectedExceptionWhat
{
	static string ErrorCreatingFolder(const string& folderPath, int errnoValue)
	{
		return ExpectedWhatString("creating folder", folderPath, errnoValue);
	}

	static string ErrorOpeningFile(const string& filePath, int errnoValue)
	{
		return ExpectedWhatString("opening file", filePath, errnoValue);
	}

	static string ErrorCreatingFile(const string& filePath, int errnoValue)
	{
		return ExpectedWhatString("creating file", filePath, errnoValue);
	}

	static string ErrorReadingFile(const string& filePath, int errnoValue)
	{
		return ExpectedWhatString("reading file", filePath, errnoValue);
	}
private:
	static string ExpectedWhatString(const char*, const string& filePath, int errnoValue)
	{
		ostringstream expectedWhatBuilder;
      const string errnoReadable = Errno::ToReadable(errnoValue);
		expectedWhatBuilder << filePath << ". Reason: " << errnoReadable << ". errno=" << errnoValue;
      const string expectedWhat = expectedWhatBuilder.str();
		return expectedWhat;
	}
};
