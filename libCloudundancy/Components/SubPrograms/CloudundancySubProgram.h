#pragma once
class Console;
struct CloudundancyArgs;

class CloudundancySubProgram
{
   friend class CloudundancySubProgramTests;
   friend class ExampleLinuxIniFileSubProgramTests;
   friend class ExampleWindowsIniFileSubProgramTests;
protected:
   unique_ptr<const Console> _console;
public:
   CloudundancySubProgram();
   virtual ~CloudundancySubProgram() = default;
   virtual int Run(const CloudundancyArgs& args);
};
