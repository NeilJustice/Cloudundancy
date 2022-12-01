#pragma once
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/UtilityComponents/Console/ConsoleColorer.h"
class ConsoleTests;

namespace Utils
{
   class Console
   {
      friend class ::ConsoleTests;
   private:
      // Function Pointers
      function<void(int)> _call_quick_exit;
      // Mutable Components
      unique_ptr<Utils::ConsoleColorer> _consoleColorer;
   public:
      Console();
      virtual ~Console();
      virtual void Write(string_view message) const;
      virtual void WriteLine(string_view message) const;
      virtual void WriteLines(const vector<string>& lines) const;
      virtual void WriteLineIf(bool doPrintMessage, string_view message) const;
      virtual void WriteLineAndExit(string_view message, int exitCode) const;
      virtual void WriteLineColor(string_view message, Color color) const;
   };
}
