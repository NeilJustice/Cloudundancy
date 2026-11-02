#pragma once
#include "libCloudundancy/Components/FileSystem/RawCFileAPI.h"

namespace Utils
{
   class RawCFileAPIMock : public Metal::Mock<RawCFileAPI>
   {
   public:
#ifdef __linux__
      METALMOCK_NONVOID2_CONST(FILE*, fopen, const fs::path&, const char*)
#elif _WIN32
      METALMOCK_NONVOID3_CONST(FILE*, wfsopen, const fs::path&, const char*, int)
#endif
      METALMOCK_NONVOID3_CONST(size_t, fread, char*, size_t, FILE*)
      METALMOCK_NONVOID3_CONST(size_t, fwrite, const char*, size_t, FILE*)
      METALMOCK_NONVOID1_CONST(int, fflush, FILE*)
   };
}
