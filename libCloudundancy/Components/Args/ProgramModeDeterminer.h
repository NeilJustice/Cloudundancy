#pragma once
class DocoptParser;

class ProgramModeDeterminer
{
   friend class ProgramModeDeterminerTests;
private:
   // Constant Components
   unique_ptr<const DocoptParser> _docoptParser;
public:
   ProgramModeDeterminer();
   virtual ~ProgramModeDeterminer();

   virtual ProgramMode DetermineProgramMode(const map<string, docopt::value>& docoptArgs) const;
};
