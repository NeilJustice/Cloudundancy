#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancy/Components/Exception/Exception.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidZeroArgMemberFunctionCaller.h"

Console::Console()
   : _consoleColorer(make_unique<ConsoleColorer>())
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

void Console::WriteLineColor(string_view message, Color color) const
{
   const bool didSetColor = _consoleColorer->SetColor(color);
   cout << message << endl;
   _consoleColorer->UnsetColor(didSetColor);
}
