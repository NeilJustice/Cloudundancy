#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancy/StaticUtilities/Exception.h"

Console::Console()
   // Function Callers
   : _call_exit(::exit)
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
