#pragma once
class CloudundancySubProgram;

class CloudundancySubProgramFactory
{
public:
   virtual shared_ptr<CloudundancySubProgram> NewCloudundancySubProgram(ProgramMode programMode) const;
   virtual ~CloudundancySubProgramFactory() = default;
};
