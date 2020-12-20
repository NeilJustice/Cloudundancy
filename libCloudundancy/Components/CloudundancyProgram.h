#pragma once
class CloudundancyArgsParser;
class CloudundancySubProgramFactory;
class CloudundancyFileCopier;
class Console;
class Environmentalist;
class Stopwatch;
template<typename ClassType, typename ArgumentType>
class TryCatchCaller;
class Watch;

class CloudundancyProgram
{
   friend class CloudundancyProgramTests;
private:
   // Function Pointers
   function<string(const exception*)> _call_Type_GetExceptionClassNameAndMessage;
   function<vector<string>(int, char* [])> _call_Vector_ArgcArgvToStringVector;

   // Function Callers
   unique_ptr<const TryCatchCaller<CloudundancyProgram, const vector<string>&>> _tryCatchCaller;
   // Constant Components
   unique_ptr<const CloudundancyArgsParser> _cloudundancyArgsParser;
   unique_ptr<const CloudundancySubProgramFactory> _cloudundancySubProgramFactory;
   unique_ptr<const Console> _console;
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
   unique_ptr<const Environmentalist> _environmentalist;
   unique_ptr<const Watch> _watch;
   // Mutable Components
   unique_ptr<Stopwatch> _stopwatch;
public:
   CloudundancyProgram() noexcept;
   virtual ~CloudundancyProgram();
   int Main(int argc, char* argv[]);
private:
   int Run(const vector<string>& stringArgs);
   int ExceptionHandler(const exception& ex, const vector<string>& stringArgs) const;
};
