#pragma once
class FCloseDeleterTests;

namespace Utils
{
   class FCloseDeleter
   {
      friend class ::FCloseDeleterTests;
   private:
      function<int(FILE*)> _call_fclose;
   public:
      FCloseDeleter();
      void operator()(FILE* rawFilePointer) const;
   };
}
