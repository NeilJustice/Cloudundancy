#pragma once

namespace Utils
{
   struct FileCopyResult
   {
      fs::path sourceFilePath;
      fs::path destinationFilePath;
      bool copySucceeded = false;
      unsigned long long numberOfBytesCopied = 0;
      unsigned long long durationInMilliseconds = 0;
      std::string copyFailureReason;
   };
}

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(Utils::FileCopyResult) == 144);
   #else
      static_assert(sizeof(Utils::FileCopyResult) == 120);
   #endif
#elifdef __linux__
   #ifdef _LIBCPP_VERSION
      static_assert(sizeof(Utils::FileCopyResult) == 96);
   #else
      static_assert(sizeof(Utils::FileCopyResult) == 136);
   #endif
#endif
