#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/CloudundancyArgsParser.h"
#include "libCloudundancy/Components/CloudundancyProgram.h"
#include "libCloudundancy/Components/Exception/TryCatchCaller.h"
#include "libCloudundancy/Components/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/Time/Watch.h"
#include "libCloudundancy/Utilities/Exception.h"
#include "libCloudundancy/Utilities/Vector.h"

CloudundancyProgram::CloudundancyProgram() noexcept
   // Function Callers
   : _call_Exception_GetExceptionClassNameAndMessage(Exception::GetExceptionClassNameAndMessage)
   , _call_Vector_ArgcArgvToStringVector(Vector::ArgcArgvToStringVector)
   // Constant Components
   , _cloudundancyArgsParser(make_unique<CloudundancyArgsParser>())
   , _cloudundancySubProgramFactory(make_unique<CloudundancySubProgramFactory>())
   , _console(make_unique<Console>())
   , _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
   , _tryCatchCaller(make_unique<TryCatchCaller<CloudundancyProgram, const vector<string>&>>())
   , _watch(make_unique<Watch>())
   // Mutable Components
   , _stopwatch(make_unique<Stopwatch>())
{
}

CloudundancyProgram::~CloudundancyProgram()
{
}

int CloudundancyProgram::Main(int argc, char* argv[])
{
   const vector<string> stringArgs = _call_Vector_ArgcArgvToStringVector(argc, argv);
   const int exitCode = _tryCatchCaller->TryCatchCall(
      this, &CloudundancyProgram::Run, stringArgs, &CloudundancyProgram::ExceptionHandler);
   return exitCode;
}

int CloudundancyProgram::Run(const std::vector<std::string>& stringArgs)
{
   _stopwatch->Start();
   const string spaceJoinedArgs = Vector::Join(stringArgs, ' ');
   const string runningMessage = "[Cloudundancy] Running: " + spaceJoinedArgs;
   _console->WriteLine(runningMessage);
   const CloudundancyArgs args = _cloudundancyArgsParser->ParseStringArgs(stringArgs);
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory->NewCloudundancySubProgram(args.programMode);
   const int exitCode = cloudundancySubProgram->Run(args);
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] OverallBackupResult: All non-ignored files and folders successfully copied to all destination folders.");
   _console->WriteLine("[Cloudundancy]  OverallElapsedTime: "  + elapsedSeconds + " seconds");
   _console->WriteLine("[Cloudundancy]            ExitCode: " + to_string(exitCode));
   return exitCode;
}

// Private Functions

int CloudundancyProgram::ExceptionHandler(const exception& ex, const vector<string>& /*stringArgs*/)
{
   const string exceptionTypeNameAndMessage = _call_Exception_GetExceptionClassNameAndMessage(&ex);
   const string fullExceptionMessage = "\n[Cloudundancy] Error: Exception thrown: " + exceptionTypeNameAndMessage;
   _console->WriteLine(fullExceptionMessage);
   _console->WriteLine("[Cloudundancy] ExitCode: 1");
   return 1;
}
