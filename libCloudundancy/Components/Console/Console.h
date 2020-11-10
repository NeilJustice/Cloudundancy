#pragma once
class ConsoleColorer;

class Console
{
   friend class ConsoleTests;
private:
   // Function Callers
   function<void(int)> _call_exit;
   // Mutable Components
   unique_ptr<ConsoleColorer> _consoleColorer;
public:
   Console();
   virtual ~Console();
	virtual void Write(string_view message) const;
	virtual void WriteLine(string_view message) const;
   virtual void WriteLineAndExit(string_view message, int exitCode) const;
   virtual void WriteLineColor(string_view message, Color color) const;
};
