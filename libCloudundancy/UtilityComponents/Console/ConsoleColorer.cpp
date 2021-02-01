#include "pch.h"
#include "libCloudundancy/UtilityComponents/Console/ConsoleColorer.h"

ConsoleColorer::ConsoleColorer() noexcept
// Function Pointers
#ifdef _WIN32
   : _call_fileno(_fileno)
   , _call_isatty(_isatty)
#else
   : _call_fileno(fileno)
   , _call_isatty(isatty)
#endif
#ifdef _WIN32
   , _call_GetStdHandle(GetStdHandle)
   , _call_SetConsoleTextAttribute(SetConsoleTextAttribute)
#endif
   // Constant Components
   , _asserter(make_unique<Asserter>())
   // Mutable Fields
   , _supportsColor(false)
   , _supportsColorHasBeenSet(false)
{
}

ConsoleColorer::~ConsoleColorer()
{
}

bool ConsoleColorer::SetTextColor(Color textColor)
{
   if (textColor == Color::White)
   {
      return false;
   }
   SetSupportsColorIfUnset();
   if (_supportsColor)
   {
      PlatformSpecificSetTextColor(textColor);
      return true;
   }
   return false;
}

void ConsoleColorer::UnsetTextColor(bool didPreviouslySetTextColor) const
{
   if (didPreviouslySetTextColor)
   {
      PlatformSpecificSetTextColor(Color::White);
   }
}

// Private Functions

const char* ConsoleColorer::ColorToLinuxColor(Color textColor) const
{
   switch (textColor)
   {
   case Color::Red: return "\033[31m";
   case Color::White: return "\033[0m";
   case Color::Teal: return "\033[34m";
   case Color::Green: return "\033[32m";
   case Color::Yellow: return "\033[33m";
   case Color::Unset:
   default: return "\033[0m";
   }
}

WindowsColor ConsoleColorer::ColorToWindowsColor(Color textColor) const
{
   switch (textColor)
   {
   case Color::Red: return WindowsColor::Red;
   case Color::White: return WindowsColor::White;
   case Color::Teal: return WindowsColor::Teal;
   case Color::Green: return WindowsColor::Green;
   case Color::Yellow: return WindowsColor::Yellow;
   case Color::Unset:
   default: return WindowsColor::White;
   };
}

void ConsoleColorer::PlatformSpecificSetTextColor(Color textColor) const
{
#if defined __linux__ || defined __APPLE__
   const char* linuxColor = ColorToLinuxColor(textColor);
   std::cout << linuxColor;
#elif _WIN32
   const HANDLE stdOutHandle = _call_GetStdHandle(STD_OUTPUT_HANDLE);
   const WindowsColor windowsColor = ColorToWindowsColor(textColor);
   const BOOL didSetConsoleTextAttr = _call_SetConsoleTextAttribute(stdOutHandle, static_cast<WORD>(windowsColor));
   _asserter->ThrowIfIntsNotEqual(1, static_cast<int>(didSetConsoleTextAttr),
      "SetConsoleTextAttribute() unexpectedly did not return 1");
#endif
}

void ConsoleColorer::SetSupportsColorIfUnset()
{
   if (!_supportsColorHasBeenSet)
   {
      _supportsColor = SupportsColor();
      _supportsColorHasBeenSet = true;
   }
}

bool ConsoleColorer::SupportsColor() const
{
   const int stdoutFileHandle = _call_fileno(stdout);
   const int isAtty = _call_isatty(stdoutFileHandle);
   const bool supportsColor = isAtty != 0;
   return supportsColor;
}
