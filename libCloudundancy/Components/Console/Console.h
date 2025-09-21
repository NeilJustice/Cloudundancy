#pragma once
#include "libCloudundancy/Enums/Color.h"
class ConsoleTests;

namespace Utils
{
   class ConsoleColorer;

   class Console
   {
      friend class ::ConsoleTests;
   private:
      // Function Pointers
      function<void(int)> _call_quick_exit;
      // Mutable Components
      unique_ptr<ConsoleColorer> _consoleColorer;
   public:
      Console();
      virtual ~Console();
      virtual void Write(string_view message) const;
      virtual void WriteLine(string_view message) const;
      virtual void WriteLines(const vector<string>& lines) const;
      virtual void WriteLineIf(bool doPrintMessage, string_view message) const;
      virtual void WriteLineAndExit(string_view message, int exitCode) const;
      virtual void WriteLineColor(string_view message, Utils::Color color) const;
   };
}
