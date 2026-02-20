#pragma once
class ProgramModeSpecificArgsParser;

class ProgramModeSpecificArgsParserFactory
{
public:
   virtual ~ProgramModeSpecificArgsParserFactory() = default;

   virtual shared_ptr<const ProgramModeSpecificArgsParser> NewProgramModeSpecificArgsParser(
      ProgramMode programMode) const;
};
