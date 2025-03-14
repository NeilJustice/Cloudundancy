#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancy/Components/CloudundancyProgram.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"

CloudundancyProgram::CloudundancyProgram() noexcept
   // Function Pointers
   : _call_Type_GetExceptionClassNameAndMessage(Type::GetExceptionClassNameAndMessage)
   , _call_Vector_ArgcArgvToStringVector(Vector::ArgcArgvToStringVector)
   // Function Callers
   , _tryCatchCaller(make_unique<Utils::TryCatchCaller<CloudundancyProgram, const vector<string>&>>())
   // Constant Components
   , _cloudundancyArgsParser(make_unique<CloudundancyArgsParser>())
   , _cloudundancySubProgramFactory(make_unique<CloudundancySubProgramFactory>())
   , _console(make_unique<Utils::Console>())
   , _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
   , _environmentService(make_unique<Utils::EnvironmentService>())
   , _watch(make_unique<Utils::Watch>())
   // Mutable Components
   , _stopwatch(make_unique<Utils::Stopwatch>())
{
}

CloudundancyProgram::~CloudundancyProgram()
{
}

int CloudundancyProgram::Main(int argc, char* argv[])
{
   if (argc == 1)
   {
      _console->WriteLine(CloudundancyArgs::CommandLineUsage);
      return 0;
   }
   const vector<string> stringArgs = _call_Vector_ArgcArgvToStringVector(argc, argv);
   int exitCode = _tryCatchCaller->TryCatchCallNonConstMemberFunction(
      this, &CloudundancyProgram::Run, stringArgs, &CloudundancyProgram::ExceptionHandler);
   return exitCode;
}

int CloudundancyProgram::Run(const std::vector<std::string>& stringArgs)
{
   _stopwatch->Start();

   const string spaceJoinedArgs = Vector::Join(stringArgs, ' ');
   const string runningLine = Utils::String::ConcatStrings("[Cloudundancy]   Running: ", spaceJoinedArgs);
   _console->WriteLine(runningLine);

   const string machineName = _environmentService->MachineName();
   const string machineNameLine = Utils::String::ConcatStrings("[Cloudundancy]   Machine: ", machineName);
   _console->WriteLine(machineNameLine);

   const string userName = _environmentService->UserName();
   const string userNameLine = Utils::String::ConcatStrings("[Cloudundancy]      User: ", userName);
   _console->WriteLine(userNameLine);

   const string startTime = _watch->DateTimeNow();
   const string startTimeLine = Utils::String::ConcatStrings("[Cloudundancy] StartTime: ", startTime);
   _console->WriteLine(startTimeLine);

   const CloudundancyArgs args = _cloudundancyArgsParser->ParseStringArgs(stringArgs);
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram = _cloudundancySubProgramFactory->NewCloudundancySubProgram(args.programMode);
   int exitCode = cloudundancySubProgram->Run(args);

   const string endTime = _watch->DateTimeNow();
   const string endTimeLine = Utils::String::ConcatStrings("[Cloudundancy]  EndTime: ", endTime);
   _console->WriteLine(endTimeLine);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string durationLine = Utils::String::ConcatStrings("[Cloudundancy] Duration: ", elapsedSeconds, " seconds");
   _console->WriteLine(durationLine);
   const string exitCodeLine = Utils::String::ConcatValues("[Cloudundancy] ExitCode: ", exitCode);
   const Utils::Color color = exitCode == 0 ? Utils::Color::Green : Utils::Color::Red;
   _console->WriteLineColor(exitCodeLine, color);
   return exitCode;
}

// Private Functions

int CloudundancyProgram::ExceptionHandler(const exception& ex, const vector<string>& /*stringArgs*/) const
{
   const string exceptionTypeNameAndMessage = _call_Type_GetExceptionClassNameAndMessage(&ex);
   const string fullExceptionMessage =
      "\n[Cloudundancy]     Error: Exception thrown: " + exceptionTypeNameAndMessage;
   _console->WriteLine(fullExceptionMessage);
   const string endTime = _watch->DateTimeNow();
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy]   EndTime: " + endTime);
   _console->WriteLine("[Cloudundancy]  Duration: " + elapsedSeconds + " seconds");
   _console->WriteLineColor("[Cloudundancy]  ExitCode: 1", Utils::Color::Red);
   return 1;
}
