#pragma once
#include "libCloudundancy/UtilityComponents/Console/Console.h"
#include "libCloudundancy/UtilityComponents/Exception/TryCatchCaller.h"
#include "libCloudundancy/UtilityComponents/Environment/EnvironmentService.h"
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"
#include "libCloudundancy/UtilityComponents/Time/Watch.h"
class CloudundancyArgsParser;
class CloudundancyFileCopier;
class CloudundancySubProgramFactory;

class CloudundancyProgram
{
   friend class CloudundancyProgramTests;
private:
   // Function Pointers
   function<string(const exception*)> _call_Type_GetExceptionClassNameAndMessage;
   function<vector<string>(int, char* [])> _call_Vector_ArgcArgvToStringVector;

   // Function Callers
   unique_ptr<const Utils::TryCatchCaller<CloudundancyProgram, const vector<string>&>> _tryCatchCaller;
   // Constant Components
   unique_ptr<const CloudundancyArgsParser> _cloudundancyArgsParser;
   unique_ptr<const CloudundancySubProgramFactory> _cloudundancySubProgramFactory;
   unique_ptr<const Time::Console> _console;
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
   unique_ptr<const Utils::EnvironmentService> _environmentService;
   unique_ptr<const Time::Watch> _watch;
   // Mutable Components
   unique_ptr<Time::Stopwatch> _stopwatch;
public:
   CloudundancyProgram() noexcept;
   virtual ~CloudundancyProgram();
   int Main(int argc, char* argv[]);
private:
   int Run(const vector<string>& stringArgs);
   int ExceptionHandler(const exception& ex, const vector<string>& stringArgs) const;
};
