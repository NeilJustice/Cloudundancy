#pragma once
class Console;

class CloudundancySubProgram
{
   friend class CloudundancySubProgramTests;
   friend class PrintExampleLinuxIniFileSubProgramTests;
   friend class PrintExampleWindowsIniFileSubProgramTests;
protected:
   unique_ptr<const Console> _console;
public:
   CloudundancySubProgram();
   virtual ~CloudundancySubProgram() = default;
   virtual int Run(const CloudundancyArgs& args);
};
