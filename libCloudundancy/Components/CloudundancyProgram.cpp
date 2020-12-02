#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/CloudundancyProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"

CloudundancyProgram::CloudundancyProgram() noexcept
   // Function Callers
   : _call_Type_GetExceptionClassNameAndMessage(Type::GetExceptionClassNameAndMessage)
   , _call_Vector_ArgcArgvToStringVector(Vector::ArgcArgvToStringVector)
   // Constant Components
   , _cloudundancyArgsParser(make_unique<CloudundancyArgsParser>())
   , _cloudundancySubProgramFactory(make_unique<CloudundancySubProgramFactory>())
   , _console(make_unique<Console>())
   , _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
   , _environmentalist(make_unique<Environmentalist>())
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
   const string runningLine = "[Cloudundancy]     Running: " + spaceJoinedArgs;
   _console->WriteLine(runningLine);

   const string machineName = _environmentalist->MachineName();
   const string machineNameLine = "[Cloudundancy] MachineName: " + machineName;
   _console->WriteLine(machineNameLine);

   const string userName = _environmentalist->UserName();
   const string userNameLine = "[Cloudundancy]    UserName: " + userName;
   _console->WriteLine(userNameLine);

   const string startTime = _watch->DateTimeNow();
   const string startTimeLine = "[Cloudundancy]   StartTime: " + startTime;
   _console->WriteLine(startTimeLine);

   const CloudundancyArgs args = _cloudundancyArgsParser->ParseStringArgs(stringArgs);
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory->NewCloudundancySubProgram(args.programMode);
   const int exitCode = cloudundancySubProgram->Run(args);

   const string endTime = _watch->DateTimeNow();
   const string endTimeLine = "[Cloudundancy]  EndTime: " + endTime;
   _console->WriteLine(endTimeLine);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Duration: "  + elapsedSeconds + " seconds");
   _console->WriteLine("[Cloudundancy] ExitCode: " + to_string(exitCode));
   return exitCode;
}

// Private Functions

int CloudundancyProgram::ExceptionHandler(const exception& ex, const vector<string>& /*stringArgs*/)
{
   const string exceptionTypeNameAndMessage = _call_Type_GetExceptionClassNameAndMessage(&ex);
   const string fullExceptionMessage =
      "\n[Cloudundancy]     Error: Exception thrown: " + exceptionTypeNameAndMessage;
   _console->WriteLine(fullExceptionMessage);
   const string endTime = _watch->DateTimeNow();
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy]   EndTime: " + endTime);
   _console->WriteLine("[Cloudundancy]  Duration: " + elapsedSeconds + " seconds");
   _console->WriteLine("[Cloudundancy]  ExitCode: 1");
   return 1;
}
