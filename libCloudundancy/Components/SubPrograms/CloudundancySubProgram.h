#pragma once

class CloudundancySubProgram
{
   friend class CloudundancySubProgramTests;
   friend class ExampleLinuxIniFileSubProgramTests;
   friend class ExampleWindowsIniFileSubProgramTests;
protected:
   // Constant Components
   unique_ptr<const Utils::Console> p_console;
public:
   CloudundancySubProgram();
   virtual ~CloudundancySubProgram();
   virtual int Run(const CloudundancyArgs& args);
};
