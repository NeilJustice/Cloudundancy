#pragma once
struct CloudundancyArgs;

class CloudundancySubProgram
{
public:
   virtual int Run(const CloudundancyArgs& args);
   virtual ~CloudundancySubProgram();
};
