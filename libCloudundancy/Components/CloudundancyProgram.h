#pragma once
class CloudundancyArgsParser;
class CloudundancySubProgramFactory;
struct CloudundancyArgs;
class Console;
class CloudundancyFileCopier;
class Stopwatch;
template<typename ClassType, typename ArgumentType>
class TryCatchCaller;
template<typename ClassType, typename ArgumentType>
class VoidOneArgMemberFunctionCaller;

class CloudundancyProgram
{
   friend class CloudundancyProgramTests;
private:
   // Constant Components
   std::unique_ptr<const CloudundancyArgsParser> _cloudundancyArgsParser;
   std::unique_ptr<const CloudundancySubProgramFactory> _cloudundancySubProgramFactory;
   std::unique_ptr<const Console> _console;
   std::unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
   std::unique_ptr<const TryCatchCaller<CloudundancyProgram, const std::vector<std::string>&>> _tryCatchCaller;
   // Function Callers
   std::function<std::string(const std::exception*)> _call_Exception_GetExceptionClassNameAndMessage;
   std::function<std::vector<std::string>(int, char* [])> _call_Vector_ArgcArgvToStringVector;
   // Mutable Components
   std::unique_ptr<Stopwatch> _stopwatch;
public:
   CloudundancyProgram() noexcept;
   virtual ~CloudundancyProgram();
   int Main(int argc, char* argv[]);
private:
   int Run(const std::vector<std::string>& stringArgs);
   int ExceptionHandler(const std::exception& ex, const std::vector<std::string>& stringArgs);
};
