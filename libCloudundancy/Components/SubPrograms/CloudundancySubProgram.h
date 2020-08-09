#pragma once
struct CloudundancyArgs;

class CloudundancySubProgram
{
public:
   virtual void Run(const CloudundancyArgs& args);
   virtual ~CloudundancySubProgram();
};
