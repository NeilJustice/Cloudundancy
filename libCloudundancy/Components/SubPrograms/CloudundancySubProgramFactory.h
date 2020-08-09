#pragma once
class CloudundancySubProgram;
enum class ProgramMode;

class CloudundancySubProgramFactory
{
public:
   virtual shared_ptr<CloudundancySubProgram> NewCloudundancySubProgram(ProgramMode programMode) const;
   virtual ~CloudundancySubProgramFactory();
};
