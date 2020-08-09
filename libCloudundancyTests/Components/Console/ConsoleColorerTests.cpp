#include "pch.h"
#include "libCloudundancy/Components/Console/ConsoleColorer.h"
#include "libCloudundancy/Components/Console/Windows/WindowsColor.h"

TESTS(ConsoleColorerTests)
AFACT(DefaultConstructor_SetsFunctionPointers_SetsBoolFieldsToFalse)
AFACT(SetColor_ColorIsWhite_DoesNotSetTextColor_ReturnsFalse)
AFACT(SetColor_ColorIsWhite_DoesNotSetTextColor_ReturnsFalse)
FACTS(ColorToWindowsColor_ReturnsWindowsColorForColor)
FACTS(ColorToLinuxColor_ReturnsLinuxColorStringForColor)
EVIDENCE

ConsoleColorer _consoleColorer;

TEST(DefaultConstructor_SetsFunctionPointers_SetsBoolFieldsToFalse)
{
   ConsoleColorer consoleColorer;
   //
#ifdef _WIN32
   STD_FUNCTION_TARGETS(::_fileno, consoleColorer._call_fileno);
   STD_FUNCTION_TARGETS(::_isatty, consoleColorer._call_isatty);
#else
   STD_FUNCTION_TARGETS(::fileno, consoleColorer._call_fileno);
   STD_FUNCTION_TARGETS(::isatty, consoleColorer._call_isatty);
#endif
#ifdef _WIN32
   STD_FUNCTION_TARGETS(::GetStdHandle, consoleColorer._call_GetStdHandle);
   STD_FUNCTION_TARGETS(::SetConsoleTextAttribute, consoleColorer._call_SetConsoleTextAttribute);
#endif
   IS_FALSE(consoleColorer._supportsColor);
   IS_FALSE(consoleColorer._supportsColorSet);
}

TEST(SetColor_ColorIsWhite_DoesNotSetTextColor_ReturnsFalse)
{
   const Color color = Color::White;
   //
   const bool didSetColor = _consoleColorer.SetColor(color);
   //
   IS_FALSE(didSetColor);
}

TEST2X2(ColorToWindowsColor_ReturnsWindowsColorForColor,
   Color color, WindowsColor expectedReturnValue,
   Color::Red, WindowsColor::Red,
   Color::White, WindowsColor::White,
   Color::Teal, WindowsColor::Teal,
   Color::Green, WindowsColor::Green,
   Color::Yellow, WindowsColor::Yellow,
   Color::Unset, WindowsColor::White,
   Color::MaxValue, WindowsColor::White)
{
   const WindowsColor windowsColor = _consoleColorer.ColorToWindowsColor(color);
   ARE_EQUAL(expectedReturnValue, windowsColor);
}

TEST2X2(ColorToLinuxColor_ReturnsLinuxColorStringForColor,
   Color color, const char* expectedReturnValue,
   Color::Red, "\033[31m",
   Color::White, "\033[0m",
   Color::Teal, "\033[34m",
   Color::Green, "\033[32m",
   Color::Yellow, "\033[33m",
   Color::Unset, "\033[0m")
{
   const char* const linuxColor = _consoleColorer.ColorToLinuxColor(color);
   ARE_EQUAL(expectedReturnValue, linuxColor);
}

RUN_TESTS(ConsoleColorerTests)
