#include "pch.h"
#include "libCloudundancy/UtilityComponents/Console/ConsoleColorer.h"

ConsoleColorer::ConsoleColorer() noexcept
#ifdef _WIN32
   : _call_fileno(::_fileno)
   , _call_isatty(::_isatty)
#else
   : _call_fileno(::fileno)
   , _call_isatty(::isatty)
#endif
#ifdef _WIN32
   , _call_GetStdHandle(::GetStdHandle)
   , _call_SetConsoleTextAttribute(::SetConsoleTextAttribute)
#endif
   , _supportsColor(false)
   , _supportsColorSet(false)
{
}

ConsoleColorer::~ConsoleColorer()
{
}

bool ConsoleColorer::SetColor(Color color)
{
   SetSupportsColorIfUnset();
   const bool doSetTextColor = color != Color::White && _supportsColor;
   if (doSetTextColor)
   {
      SetTextColor(color);
      return true;
   }
   return false;
}

void ConsoleColorer::UnsetColor(bool didPreviouslySetTextColor) const
{
   if (didPreviouslySetTextColor)
   {
      SetTextColor(Color::White);
   }
}

void ConsoleColorer::SetSupportsColorIfUnset()
{
   if (!_supportsColorSet)
   {
      _supportsColor = SupportsColor();
      _supportsColorSet = true;
   }
}

bool ConsoleColorer::SupportsColor() const
{
   const int stdoutFileHandle = _call_fileno(stdout);
   const int isAtty = _call_isatty(stdoutFileHandle);
   const bool supportsColor = isAtty != 0;
   return supportsColor;
}

void ConsoleColorer::SetTextColor(Color color) const
{
#if defined __linux__
   const char* linuxColor = ColorToLinuxColor(color);
   std::cout << linuxColor;
#elif _WIN32
   const HANDLE stdOutHandle = _call_GetStdHandle(STD_OUTPUT_HANDLE);
   const WindowsColor windowsColor = ColorToWindowsColor(color);
   const BOOL didSetConsoleTextAttr = _call_SetConsoleTextAttribute(stdOutHandle, static_cast<WORD>(windowsColor));
   release_assert(didSetConsoleTextAttr == TRUE);
#endif
}

WindowsColor ConsoleColorer::ColorToWindowsColor(Color color) noexcept
{
   switch (color)
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

const char* ConsoleColorer::ColorToLinuxColor(Color color) noexcept
{
   switch (color)
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
