#pragma once

struct FileCopyResult
{
   fs::path sourceFilePath;
   fs::path destinationFilePath;
	bool copySucceeded = false;
   unsigned long long numberOfBytesCopied = 0;
   unsigned long long durationInMilliseconds = 0;
	std::string errorMessage;
};
