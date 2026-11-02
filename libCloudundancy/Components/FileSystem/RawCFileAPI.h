#pragma once

namespace Utils
{
   class RawCFileAPI
   {
      friend class RawCFileAPITests;
   private:

   public:
      virtual ~RawCFileAPI() = default;

#ifdef __linux__
      virtual FILE* fopen(const fs::path& filePath, const char* fileOpenMode) const;
#elif _WIN32
      virtual FILE* wfsopen(const fs::path& filePath, const char* fileOpenMode, int fileOpenFlags) const;
#endif
      virtual size_t fread(char* outFileBytes, size_t numberOfBytesToRead, FILE* filePointer) const;
      virtual size_t fwrite(const char* bytes, size_t bytesSize, FILE* filePointer) const;
      virtual int fflush(FILE* filePointer) const;
   };
}
