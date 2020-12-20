#include "pch.h"
#include "libCloudundancy/UtilityComponents/Console/Console.h"

Console::Console()
   // Function Pointers
   : _call_exit(::_exit)
   // Mutable Components
   , _consoleColorer(make_unique<ConsoleColorer>())

{
}

Console::~Console()
{
}

void Console::Write(string_view message) const
{
   cout << message;
}

void Console::WriteLine(string_view message) const
{
   cout << message << '\n';
}

void Console::WriteLines(const vector<string>& lines) const
{
   for (const string& line : lines)
   {
      cout << line << '\n';
   }
}

void Console::WriteLineIf(bool doPrintMessage, string_view message) const
{
   if (doPrintMessage)
   {
      cout << message << '\n';
   }
}

void Console::WriteLineAndExit(string_view message, int exitCode) const
{
   cout << message << '\n';
   _call_exit(exitCode);
}

void Console::WriteLineColor(string_view message, Color color) const
{
   const bool didSetColor = _consoleColorer->SetColor(color);
   cout << message << '\n';
   _consoleColorer->UnsetColor(didSetColor);
}
