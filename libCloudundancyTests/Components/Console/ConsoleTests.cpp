#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsConsoleColorer)
AFACT(Write_DoesNotThrow)
AFACT(WriteLine_DoesNotThrow)
AFACT(WriteLineColor_DoesNotThrow)
EVIDENCE

Console _console;

TEST(DefaultConstructor_NewsConsoleColorer)
{
   Console console;
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
}

TEST(Write_DoesNotThrow)
{
   DOES_NOT_THROW(_console.Write(ZenUnit::Random<string>()));
   const string_view stringView;
   DOES_NOT_THROW(_console.Write(stringView));
}

TEST(WriteLine_DoesNotThrow)
{
   DOES_NOT_THROW(_console.WriteLine(ZenUnit::Random<string>()));
   const string_view stringView;
   DOES_NOT_THROW(_console.WriteLine(stringView));
}

TEST(WriteLineColor_DoesNotThrow)
{
   const string message = ZenUnit::Random<string>();
   const Color color = ZenUnit::RandomEnum<Color>(Color::MaxValue);
   //
   DOES_NOT_THROW(_console.WriteLineColor(message, color));
}

RUN_TESTS(ConsoleTests)
