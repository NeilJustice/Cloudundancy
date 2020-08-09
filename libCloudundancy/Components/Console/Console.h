#pragma once
#include "libCloudundancy/Components/Console/Windows/WindowsColor.h"
#include "libCloudundancy/Components/Console/Color.h"
class ConsoleTests;

class ConsoleColorer;
template<typename ClassType>
class VoidZeroArgMemberFunctionCaller;

class Console
{
   friend class ::ConsoleTests;
private:
   unique_ptr<ConsoleColorer> _consoleColorer;
   unique_ptr<const VoidZeroArgMemberFunctionCaller<Console>> _voidZeroArgMemberFunctionCaller;
public:
   Console();
   virtual ~Console();
	virtual void Write(string_view message) const;
	virtual void WriteLine(string_view message) const;
   virtual void WriteLineColor(string_view message, Color color) const;
#ifdef _WIN32
	virtual WindowsColor SetTextColor(WindowsColor windowsColor) const;
#endif
};
