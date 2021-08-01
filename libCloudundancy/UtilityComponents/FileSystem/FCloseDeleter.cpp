#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FCloseDeleter.h"

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
      const string exceptionMessage = String::ConcatValues("fclose(rawFilePointer) returned ", fcloseReturnValue);
      throw runtime_error(exceptionMessage);
   }
}
