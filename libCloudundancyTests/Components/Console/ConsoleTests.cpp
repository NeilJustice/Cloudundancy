#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancyTests/Components/Console/MetalMock/ConsoleColorerMock.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsConsoleColorer)
AFACT(Write_WritesMessageWithoutNewline)
AFACT(WriteLine_WritesMessageAndNewline)
AFACT(WriteLines_EmptyStringsVector_DoesNothing)
AFACT(WriteLines_NonEmptyStringsVector_WritesStringsToConsole)
AFACT(WriteLineIf_DoPrintMessageIsFalse_Returns)
AFACT(WriteLineIf_DoPrintMessageIsTrue_WritesMessageToCoutWithNewline)
AFACT(WriteLineAndExit_WritesMessageAndNewline_ExitsWithExitCode)
AFACT(WriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
EVIDENCE

Utils::Console _console;
// Function Pointers
METALMOCK_VOID1_STATIC_OR_FREE(_call_quick_exit, int)
// Mutable Components
Utils::ConsoleColorerMock* _consoleColorerMock = nullptr;

STARTUP
{
   // Function Pointers
   _console._call_quick_exit = BIND_1ARG_METALMOCK_OBJECT(_call_quick_exitMock);
   // Mutable Components
   _console._consoleColorer.reset(_consoleColorerMock = new Utils::ConsoleColorerMock);
}

TEST(DefaultConstructor_NewsConsoleColorer)
{
   Utils::Console console;
   // Function Pointers
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
   // Mutable Components
   STD_FUNCTION_TARGETS(_exit, console._call_quick_exit);
}

TEST(Write_WritesMessageWithoutNewline)
{
   DOES_NOT_THROW(_console.Write(ZenUnit::Random<string>()));
   const string_view stringView{};
   DOES_NOT_THROW(_console.Write(stringView));
}

TEST(WriteLine_WritesMessageAndNewline)
{
   DOES_NOT_THROW(_console.WriteLine(ZenUnit::Random<string>()));
   const string_view stringView{};
   DOES_NOT_THROW(_console.WriteLine(stringView));
}

TEST(WriteLines_EmptyStringsVector_DoesNothing)
{
   const vector<string> emptyLines;
   _console.WriteLines(emptyLines);
}

TEST(WriteLines_NonEmptyStringsVector_WritesStringsToConsole)
{
   const vector<string> nonEmptyLines = ZenUnit::RandomNonEmptyVector<string>();
   _console.WriteLines(nonEmptyLines);
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
   _call_quick_exitMock.Expect();
   const int exitCode = ZenUnit::Random<int>();
   //
   _console.WriteLineAndExit(ZenUnit::Random<string>(), exitCode);
   //
   METALMOCK(_call_quick_exitMock.CalledOnceWith(exitCode));
}

TEST(WriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
{
   const bool didSetTextColor = _consoleColorerMock->SetTextColorMock.ReturnRandom();
   _consoleColorerMock->UnsetTextColorMock.Expect();
   const string message = ZenUnit::Random<string>();
   const Utils::Color color = ZenUnit::RandomEnum<Utils::Color>();
   //
   _console.WriteLineColor(message, color);
   //
   METALMOCKTHEN(_consoleColorerMock->SetTextColorMock.CalledOnceWith(color)).Then(
   METALMOCKTHEN(_consoleColorerMock->UnsetTextColorMock.CalledOnceWith(didSetTextColor)));
}

RUN_TESTS(ConsoleTests)
