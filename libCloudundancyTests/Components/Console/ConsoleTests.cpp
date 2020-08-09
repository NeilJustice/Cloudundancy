#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancy/Components/Function/Member/VoidZeroArgMemberFunctionCaller.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Write_CodeCoverage)
AFACT(WriteLine_CodeCoverage)
AFACT(WriteLineColor_CodeCoverage)
EVIDENCE

Console _console;
VoidZeroArgMemberFunctionCallerMock<Console>* _voidZeroArgMemberFunctionCallerMock = nullptr;

STARTUP
{
   _console._voidZeroArgMemberFunctionCaller.reset(
      _voidZeroArgMemberFunctionCallerMock = new VoidZeroArgMemberFunctionCallerMock<Console>);
}

TEST(DefaultConstructor_NewsComponents)
{
   Console console;
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
   DELETE_TO_ASSERT_NEWED(console._voidZeroArgMemberFunctionCaller);
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
