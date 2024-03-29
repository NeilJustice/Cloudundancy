#pragma once
class WatchTests;

namespace Utils
{
   class CRTWatch;

   class Watch
   {
      friend class ::WatchTests;
   private:
      // Constant Components
      unique_ptr<const CRTWatch> _crtWatch;
   public:
      Watch() noexcept;
      virtual ~Watch();
      virtual string DateTimeNow() const;
      virtual string DateTimeNowForFileNames() const;
   private:
      virtual tm TMNow() const;
      static void Write8601Date(const tm& tmValue, char* outChars);
   };
}
