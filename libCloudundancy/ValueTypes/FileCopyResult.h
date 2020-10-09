#pragma once

struct FileCopyResult
{
   fs::path sourceFilePath;
   fs::path destinationFilePath;
	bool copySucceeded;
   unsigned long long numberOfBytesCopied;
   unsigned long long durationInMilliseconds;
	std::string errorMessage;

   FileCopyResult();
};
