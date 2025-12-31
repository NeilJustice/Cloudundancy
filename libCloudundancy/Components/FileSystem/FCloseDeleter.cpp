#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FCloseDeleter.h"

namespace Utils
{
   FCloseDeleter::FCloseDeleter()
      // Function Pointers
      : _call_fclose(fclose)
   {
   }

   void FCloseDeleter::operator()(FILE* rawFilePointer) const
   {
      const int fcloseReturnValue = _call_fclose(rawFilePointer);
      if (fcloseReturnValue != 0)
      {
         const string exceptionMessage = Utils::String::ConcatValues("fclose(rawFilePointer) returned ", fcloseReturnValue);
         throw runtime_error(exceptionMessage);
      }
   }
}
