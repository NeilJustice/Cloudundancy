#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidZeroArgMemberFunctionCaller.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Write_CodeCoverage)
AFACT(WriteLine_CodeCoverage)
AFACT(WriteLineColor_CodeCoverage)
EVIDENCE

Console _console;

TEST(DefaultConstructor_NewsComponents)
{
   Console console;
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
}

TEST(Write_CodeCoverage)
{
   _console.Write("");
   _console.Write(ZenUnit::Random<string>());
   const string_view stringView;
   _console.Write(stringView);
}

TEST(WriteLine_CodeCoverage)
{
   _console.WriteLine("");
   _console.WriteLine(ZenUnit::Random<string>());
   const string_view stringView;
   _console.WriteLine(stringView);
}

TEST(WriteLineColor_CodeCoverage)
{
   const string message = ZenUnit::Random<string>();
   const Color color = ZenUnit::RandomEnum<Color>(Color::MaxValue);
   //
   _console.WriteLineColor(message, color);
}

RUN_TESTS(ConsoleTests)
