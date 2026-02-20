#pragma once
class CloudundancySubProgram;

class CloudundancySubProgramFactory
{
public:
   virtual ~CloudundancySubProgramFactory() = default;

   virtual shared_ptr<CloudundancySubProgram> NewCloudundancySubProgram(ProgramMode programMode) const;
};
