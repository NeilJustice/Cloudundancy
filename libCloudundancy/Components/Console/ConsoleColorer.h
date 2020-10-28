#pragma once
enum class WindowsColor;

class ConsoleColorer
{
   friend class ConsoleColorerTests;
private:
   std::function<int(FILE*)> _call_fileno;
   std::function<int(int)> _call_isatty;
#if defined _WIN32
   std::function<HANDLE(DWORD)> _call_GetStdHandle;
   std::function<BOOL(HANDLE, WORD)> _call_SetConsoleTextAttribute;
#endif
   bool _supportsColor;
   bool _supportsColorSet;
public:
   ConsoleColorer() noexcept;
   virtual ~ConsoleColorer();
   virtual bool SetColor(Color color);
   virtual void UnsetColor(bool didPreviouslySetTextColor) const;
private:
   void SetSupportsColorIfUnset();
   bool SupportsColor() const;
   static const char* ColorToLinuxColor(Color color) noexcept;
   static WindowsColor ColorToWindowsColor(Color color) noexcept;
   void SetTextColor(Color color) const;
};
