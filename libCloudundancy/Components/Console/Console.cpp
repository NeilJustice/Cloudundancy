#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancy/Components/Exception/Exception.h"
#include "libCloudundancy/Components/Function/Member/VoidZeroArgMemberFunctionCaller.h"

Console::Console()
   : _consoleColorer(make_unique<ConsoleColorer>())
   , _voidZeroArgMemberFunctionCaller(make_unique<VoidZeroArgMemberFunctionCaller<Console>>())
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

#ifdef _WIN32
WindowsColor Console::SetTextColor(WindowsColor windowsColor) const
{
   const HANDLE stdOutHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
   ::GetConsoleScreenBufferInfo(stdOutHandle, &consoleScreenBufferInfo);
   const WindowsColor previousConsoleColor
      = static_cast<WindowsColor>(consoleScreenBufferInfo.wAttributes);
   ::SetConsoleTextAttribute(stdOutHandle, static_cast<WORD>(windowsColor));
   return previousConsoleColor;
}
#endif
