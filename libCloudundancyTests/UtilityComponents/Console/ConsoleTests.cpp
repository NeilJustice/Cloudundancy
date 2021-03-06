#include "pch.h"
#include "libCloudundancy/UtilityComponents/Console/Console.h"
#include "libCloudundancy/UtilityComponents/Console/ConsoleColorer.h"
#include "libCloudundancyTests/UtilityComponents/Console/MetalMock/ConsoleColorerMock.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsConsoleColorer)
AFACT(Write_WritesMessageWithoutNewline)
AFACT(WriteLine_WritesMessageAndNewline)
AFACT(WriteLines_WritesLinesToCoutWithNewline)
AFACT(WriteLineIf_DoPrintMessageIsFalse_Returns)
AFACT(WriteLineIf_DoPrintMessageIsTrue_WritesMessageToCoutWithNewline)
AFACT(WriteLineAndExit_WritesMessageAndNewline_ExitsWithExitCode)
AFACT(WriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
EVIDENCE

Console _console;
// Function Pointers
METALMOCK_VOID1_FREE(exit, int)
// Mutable Components
ConsoleColorerMock* _consoleColorerMock = nullptr;

STARTUP
{
   // Function Pointers
   _console._call_exit = BIND_1ARG_METALMOCK_OBJECT(exitMock);
   // Mutable Components
   _console._consoleColorer.reset(_consoleColorerMock = new ConsoleColorerMock);
}

TEST(DefaultConstructor_NewsConsoleColorer)
{
   Console console;
   // Function Pointers
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
   // Mutable Components
   STD_FUNCTION_TARGETS(_exit, console._call_exit);
}

TEST(Write_WritesMessageWithoutNewline)
{
   DOES_NOT_THROW(_console.Write(ZenUnit::Random<string>()));
   const string_view stringView;
   DOES_NOT_THROW(_console.Write(stringView));
}

TEST(WriteLine_WritesMessageAndNewline)
{
   DOES_NOT_THROW(_console.WriteLine(ZenUnit::Random<string>()));
   const string_view stringView;
   DOES_NOT_THROW(_console.WriteLine(stringView));
}

TEST(WriteLines_WritesLinesToCoutWithNewline)
{
   const vector<string> lines = ZenUnit::RandomVector<string>();
   _console.WriteLines(lines);
}

TEST(WriteLineIf_DoPrintMessageIsFalse_Returns)
{
   _console.WriteLineIf(false, ZenUnit::Random<string>());
}

TEST(WriteLineIf_DoPrintMessageIsTrue_WritesMessageToCoutWithNewline)
{
   _console.WriteLineIf(true, ZenUnit::Random<string>());
}

TEST(WriteLineAndExit_WritesMessageAndNewline_ExitsWithExitCode)
{
   exitMock.Expect();
   const int exitCode = ZenUnit::Random<int>();
   //
   _console.WriteLineAndExit(ZenUnit::Random<string>(), exitCode);
   //
   METALMOCK(exitMock.CalledOnceWith(exitCode));
}

TEST(WriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
{
   const bool didSetTextColor = _consoleColorerMock->SetTextColorMock.ReturnRandom();
   _consoleColorerMock->UnsetTextColorMock.Expect();
   const string message = ZenUnit::Random<string>();
   const Color color = ZenUnit::RandomEnum<Color>(Color::MaxValue);
   //
   _console.WriteLineColor(message, color);
   //
   METALMOCK(_consoleColorerMock->SetTextColorMock.CalledOnceWith(color));
   METALMOCK(_consoleColorerMock->UnsetTextColorMock.CalledOnceWith(didSetTextColor));
}

RUN_TESTS(ConsoleTests)
