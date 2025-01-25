#include "pch.h"
#include "libCloudundancy/UtilityComponents/Console/ConsoleColorer.h"

TESTS(ConsoleColorerTests)
AFACT(DefaultConstructor_SetsFunctionPointers_SetsBoolFieldsToFalse)
AFACT(SetTextColor_ColorIsWhite_ReturnsFalse)
FACTS(SetTextColor_ColorIsNotWhite_CallsSetSupportsColorIfUnset_DoesNotSupportColor_ReturnsFalse)
FACTS(SetTextColor_ColorIsNotWhite_ConsoleSupportsColorIsTrue_SetsTextColor_ReturnsTrue)
AFACT(UnsetTextColor_DidPreviouslySetTextColorIsFalse_DoesNothing)
AFACT(UnsetTextColor_DidPreviouslySetTextColorIsTrue_CallsSetTextColorWhite)
// Private Functions
FACTS(ColorToLinuxColor_ReturnsLinuxColorStringForColor)
FACTS(ColorToWindowsColor_ReturnsWindowsColorForColor)
#if defined __linux__
AFACT(Linux__SetTextColor_CallsColorToLinuxColor_InsertionOperatorsLinuxColorToCout)
#elif _WIN32
AFACT(Windows__SetTextColor_CallsSetConsoleTextAttributeToWindowsColor)
#endif
AFACT(SetSupportsColorIfUnset_SupportsColorBeenSetIsTrue_DoesNothing)
AFACT(SetSupportsColorIfUnset_SupportsColorBeenSetIsFalse_SetsSupportsColorToResultOfCallingSupportsColor_SetsSupportsColorHasBeenSetToTrue)
FACTS(SupportsColor_CallsFileno_CallsIsAtty_ReturnsTrueIfIsAttyReturnValueIsNot0)
EVIDENCE

Utils::ConsoleColorer _consoleColorer;
// Function Pointers
METALMOCK_NONVOID1_STATIC_OR_FREE(int, _call_fileno, FILE*)
METALMOCK_NONVOID1_STATIC_OR_FREE(int, _call_isatty, int)
// Constant Components
Utils::AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _consoleColorer._call_fileno = BIND_1ARG_METALMOCK_OBJECT(_call_filenoMock);
   _consoleColorer._call_isatty = BIND_1ARG_METALMOCK_OBJECT(_call_isattyMock);
   // Constant Components
   _consoleColorer._asserter.reset(_asserterMock = new Utils::AsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_SetsBoolFieldsToFalse)
{
   Utils::ConsoleColorer consoleColorer;
   // Function Pointers
#ifdef _WIN32
   STD_FUNCTION_TARGETS(_fileno, consoleColorer._call_fileno);
   STD_FUNCTION_TARGETS(_isatty, consoleColorer._call_isatty);
   STD_FUNCTION_TARGETS(GetStdHandle, consoleColorer._call_GetStdHandle);
   STD_FUNCTION_TARGETS(SetConsoleTextAttribute, consoleColorer._call_SetConsoleTextAttribute);
#else
   STD_FUNCTION_TARGETS(fileno, consoleColorer._call_fileno);
   STD_FUNCTION_TARGETS(isatty, consoleColorer._call_isatty);
#endif
   // Constant Components
   DELETE_TO_ASSERT_NEWED(consoleColorer._asserter);
   // Mutable Fields
   IS_FALSE(consoleColorer._supportsColor);
   IS_FALSE(consoleColorer._supportsColorHasBeenSet);
}

TEST(SetTextColor_ColorIsWhite_ReturnsFalse)
{
   const Utils::Color color = Utils::Color::White;
   //
   const bool didSetColor = _consoleColorer.SetTextColor(color);
   //
   IS_FALSE(didSetColor);
}

TEST1X1(SetTextColor_ColorIsNotWhite_CallsSetSupportsColorIfUnset_DoesNotSupportColor_ReturnsFalse,
   Utils::Color nonWhiteColor,
   Utils::Color::Green,
   Utils::Color::Red)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_VOID0(SetSupportsColorIfUnset)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.Expect();
   consoleColorerSelfMocked._supportsColor = false;
   //
   const bool didSetTextColor = consoleColorerSelfMocked.SetTextColor(nonWhiteColor);
   //
   METALMOCK(consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.CalledOnce());
   IS_FALSE(didSetTextColor);
}

TEST1X1(SetTextColor_ColorIsNotWhite_ConsoleSupportsColorIsTrue_SetsTextColor_ReturnsTrue,
   Utils::Color nonWhiteColor,
   Utils::Color::Green,
   Utils::Color::Red)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_VOID0(SetSupportsColorIfUnset)
      METALMOCK_VOID1_CONST(PlatformSpecificSetTextColor, Utils::Color)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.Expect();
   consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.Expect();
   consoleColorerSelfMocked._supportsColor = true;
   //
   const bool didSetTextColor = consoleColorerSelfMocked.SetTextColor(nonWhiteColor);
   //
   METALMOCKTHEN(consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.CalledOnce()).Then(
   METALMOCKTHEN(consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.CalledOnceWith(nonWhiteColor)));
   IS_TRUE(didSetTextColor);
}

TEST(UnsetTextColor_DidPreviouslySetTextColorIsFalse_DoesNothing)
{
   _consoleColorer.UnsetTextColor(false);
}

TEST(UnsetTextColor_DidPreviouslySetTextColorIsTrue_CallsSetTextColorWhite)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_VOID1_CONST(PlatformSpecificSetTextColor, Utils::Color)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.Expect();
   //
   consoleColorerSelfMocked.UnsetTextColor(true);
   //
   METALMOCK(consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.CalledOnceWith(Utils::Color::White));
}

// Private Functions

TEST2X2(ColorToLinuxColor_ReturnsLinuxColorStringForColor,
   Utils::Color color, const char* expectedReturnValue,
   Utils::Color::Red, "\033[31m",
   Utils::Color::White, "\033[0m",
   Utils::Color::Teal, "\033[34m",
   Utils::Color::Green, "\033[32m",
   Utils::Color::Yellow, "\033[33m",
   Utils::Color::Unset, "\033[0m")
{
   const char* const linuxColor = _consoleColorer.ColorToLinuxColor(color);
   ARE_EQUAL(expectedReturnValue, linuxColor);
}

TEST2X2(ColorToWindowsColor_ReturnsWindowsColorForColor,
   Utils::Color color, WindowsColor expectedReturnValue,
   Utils::Color::Red, WindowsColor::Red,
   Utils::Color::White, WindowsColor::White,
   Utils::Color::Teal, WindowsColor::Teal,
   Utils::Color::Green, WindowsColor::Green,
   Utils::Color::Yellow, WindowsColor::Yellow,
   Utils::Color::Unset, WindowsColor::White,
   Utils::Color::MaxValue, WindowsColor::White)
{
   const WindowsColor windowsColor = _consoleColorer.ColorToWindowsColor(color);
   ARE_EQUAL(expectedReturnValue, windowsColor);
}

#if defined __linux__

TEST(Linux__SetTextColor_CallsColorToLinuxColor_InsertionOperatorsLinuxColorToCout)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID1_CONST(const char*, ColorToLinuxColor, Utils::Color)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.ColorToLinuxColorMock.ReturnRandom();
   const Utils::Color color = ZenUnit::RandomEnum<Utils::Color>();
   //
   consoleColorerSelfMocked.PlatformSpecificSetTextColor(color);
   //
   METALMOCK(consoleColorerSelfMocked.ColorToLinuxColorMock.CalledOnceWith(color));
}

#elif _WIN32

TEST(Windows__SetTextColor_CallsSetConsoleTextAttributeToWindowsColor)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID1_STATIC_OR_FREE(HANDLE, _call_GetStdHandle, DWORD)
      METALMOCK_NONVOID2_STATIC_OR_FREE(BOOL, _call_SetConsoleTextAttribute, HANDLE, WORD)
      METALMOCK_NONVOID1_CONST(WindowsColor, ColorToWindowsColor, Utils::Color)
      Utils::AsserterMock* _asserterMock = nullptr;
      ConsoleColorerSelfMocked()
      {
         _call_GetStdHandle = BIND_1ARG_METALMOCK_OBJECT(_call_GetStdHandleMock);
         _call_SetConsoleTextAttribute = BIND_2ARG_METALMOCK_OBJECT(_call_SetConsoleTextAttributeMock);
         _asserter.reset(_asserterMock = new Utils::AsserterMock);
      }
   } consoleColorerSelfMocked;

   const HANDLE stdOutHandle = reinterpret_cast<HANDLE>(ZenUnit::Random<unsigned long long>());
   consoleColorerSelfMocked._call_GetStdHandleMock.Return(stdOutHandle);

   const WindowsColor windowsTextColor = ZenUnit::RandomEnum<WindowsColor>();
   consoleColorerSelfMocked.ColorToWindowsColorMock.Return(windowsTextColor);

   const BOOL didSetConsoleTextAttr = consoleColorerSelfMocked._call_SetConsoleTextAttributeMock.ReturnRandom();

   consoleColorerSelfMocked._asserterMock->ThrowIfIntsNotEqualMock.Expect();

   const Utils::Color textColor = ZenUnit::RandomEnum<Utils::Color>();
   //
   consoleColorerSelfMocked.PlatformSpecificSetTextColor(textColor);
   //
   METALMOCKTHEN(consoleColorerSelfMocked._call_GetStdHandleMock.CalledOnceWith(STD_OUTPUT_HANDLE)).Then(
   METALMOCKTHEN(consoleColorerSelfMocked.ColorToWindowsColorMock.CalledOnceWith(textColor))).Then(
   METALMOCKTHEN(consoleColorerSelfMocked._call_SetConsoleTextAttributeMock.CalledOnceWith(stdOutHandle, static_cast<WORD>(windowsTextColor)))).Then(
   METALMOCKTHEN(consoleColorerSelfMocked._asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(1, static_cast<int>(didSetConsoleTextAttr),
      "SetConsoleTextAttribute() unexpectedly did not return 1")));
}

#endif

TEST(SetSupportsColorIfUnset_SupportsColorBeenSetIsTrue_DoesNothing)
{
   _consoleColorer._supportsColorHasBeenSet = true;
   _consoleColorer.SetSupportsColorIfUnset();
}

TEST(SetSupportsColorIfUnset_SupportsColorBeenSetIsFalse_SetsSupportsColorToResultOfCallingSupportsColor_SetsSupportsColorHasBeenSetToTrue)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID0_CONST(bool, SupportsColor)
   } consoleColorerSelfMocked;
   const bool supportsColor = consoleColorerSelfMocked.SupportsColorMock.ReturnRandom();
   consoleColorerSelfMocked._supportsColorHasBeenSet = false;
   //
   consoleColorerSelfMocked.SetSupportsColorIfUnset();
   //
   METALMOCK(consoleColorerSelfMocked.SupportsColorMock.CalledOnce());
   ARE_EQUAL(supportsColor, consoleColorerSelfMocked._supportsColor);
   IS_TRUE(consoleColorerSelfMocked._supportsColorHasBeenSet);
}

TEST2X2(SupportsColor_CallsFileno_CallsIsAtty_ReturnsTrueIfIsAttyReturnValueIsNot0,
   int isattyReturnValue, bool expectedReturnValue,
   0, false,
   -1, true,
   1, true,
   2, true)
{
   const int stdoutFileHandle = _call_filenoMock.ReturnRandom();
   _call_isattyMock.Return(isattyReturnValue);
   //
   const bool supportsColor = _consoleColorer.SupportsColor();
   //
   METALMOCKTHEN(_call_filenoMock.CalledOnceWith(stdout)).Then(
   METALMOCKTHEN(_call_isattyMock.CalledOnceWith(stdoutFileHandle)));
   ARE_EQUAL(expectedReturnValue, supportsColor);
}

RUN_TESTS(ConsoleColorerTests)
