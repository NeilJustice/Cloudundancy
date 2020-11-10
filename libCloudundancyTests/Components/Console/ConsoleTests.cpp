#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsConsoleColorer)
AFACT(Write_WritesMessageWithoutNewline)
AFACT(WriteLine_WritesMessageAndNewline)
AFACT(WriteLineAndExit_WritesMessageAndNewline_ExitsWithExitCode)
AFACT(WriteLineColor_SetsConsoleColor_WritesMessageThenNewline_UnsetsColor)
EVIDENCE

Console _console;
METALMOCK_VOID1_FREE(exit, int)

STARTUP
{
   _console._call_exit = BIND_1ARG_METALMOCK_OBJECT(exitMock);
}

TEST(DefaultConstructor_NewsConsoleColorer)
{
   Console console;
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
   STD_FUNCTION_TARGETS(::exit, console._call_exit);
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

TEST(WriteLineAndExit_WritesMessageAndNewline_ExitsWithExitCode)
{
   exitMock.Expect();
   const int exitCode = ZenUnit::Random<int>();
   //
   _console.WriteLineAndExit(ZenUnit::Random<string>(), exitCode);
   //
   METALMOCK(exitMock.CalledOnceWith(exitCode));
}

TEST(WriteLineColor_SetsConsoleColor_WritesMessageThenNewline_UnsetsColor)
{
   const string message = ZenUnit::Random<string>();
   const Color color = ZenUnit::RandomEnum<Color>(Color::MaxValue);
   //
   DOES_NOT_THROW(_console.WriteLineColor(message, color));
}

RUN_TESTS(ConsoleTests)
