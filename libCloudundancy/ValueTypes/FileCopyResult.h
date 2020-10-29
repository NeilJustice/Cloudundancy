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

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(FileCopyResult) == 144);
   #else
      static_assert(sizeof(FileCopyResult) == 120);
   #endif
#endif
