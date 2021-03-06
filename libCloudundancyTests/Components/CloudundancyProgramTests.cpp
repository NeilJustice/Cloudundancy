#include "pch.h"
#include "libCloudundancy/Components/CloudundancyProgram.h"
#include "libCloudundancyTests/Components/Args/MetalMock/CloudundancyArgsParserMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniFileReaderMock.h"
#include "libCloudundancyTests/Components/SubPrograms/MetalMock/CloudundancySubProgramFactoryMock.h"
#include "libCloudundancyTests/Components/SubPrograms/MetalMock/CloudundancySubProgramMock.h"

TESTS(CloudundancyProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Main_ArgcIs1_WriteLinesCommandLineUsage_Returns0)
AFACT(Main_ArgcIs2OrGreater_CallsTryCatchCallRunWithStringArgs_ReturnsExitCodeFromCallingRun)
FACTS(Run_PrintsCommandLineAndStartTimeAndMachineName_ParsesArgs_NewsAndRunsSubProgram_PrintsEndTimeAndElapsedTime_ExitsWithSubProgramExitCode_WritesExitCodeInGreenIf0OtherwiseRed)
// Private Functions
AFACT(ExceptionHandler_PrintsExceptionClassNameAndMessage_Returns1)
EVIDENCE

CloudundancyProgram _cloudundancyProgram;
// Function Callers
METALMOCK_NONVOID2_STATIC(vector<string>, Vector, ArgcArgvToStringVector, int, char**)
METALMOCK_NONVOID1_STATIC(string, Type, GetExceptionClassNameAndMessage, const exception*)
// Function Callers
TryCatchCallerMock<CloudundancyProgram, const vector<string>&>* _tryCatchCallerMock = nullptr;
// Constant Components
CloudundancyArgsParserMock* _cloudundancyArgsParserMock = nullptr;
CloudundancySubProgramFactoryMock* _cloudundancySubProgramFactoryMock = nullptr;
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
EnvironmentServiceMock* _environmentServiceMock = nullptr;
WatchMock* _watchMock = nullptr;
// Mutable Components
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyProgram._call_Type_GetExceptionClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(GetExceptionClassNameAndMessageMock);
   _cloudundancyProgram._call_Vector_ArgcArgvToStringVector = BIND_2ARG_METALMOCK_OBJECT(ArgcArgvToStringVectorMock);
   // Function Callers
   _cloudundancyProgram._tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock<CloudundancyProgram, const vector<string>&>);
   // Constant Components
   _cloudundancyProgram._cloudundancyArgsParser.reset(_cloudundancyArgsParserMock = new CloudundancyArgsParserMock);
   _cloudundancyProgram._cloudundancySubProgramFactory.reset(_cloudundancySubProgramFactoryMock = new CloudundancySubProgramFactoryMock);
   _cloudundancyProgram._environmentService.reset(_environmentServiceMock = new EnvironmentServiceMock);
   _cloudundancyProgram._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _cloudundancyProgram._watch.reset(_watchMock = new WatchMock);
   // Mutable Components
   _cloudundancyProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyProgram cloudundancyProgram;
   // Function Pointers
   STD_FUNCTION_TARGETS(Type::GetExceptionClassNameAndMessage, cloudundancyProgram._call_Type_GetExceptionClassNameAndMessage);
   STD_FUNCTION_TARGETS(Vector::ArgcArgvToStringVector, cloudundancyProgram._call_Vector_ArgcArgvToStringVector);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._tryCatchCaller);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancyArgsParser);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancySubProgramFactory);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancyFileCopier);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._environmentService);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._watch);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._stopwatch);
}

TEST(Main_ArgcIs1_WriteLinesCommandLineUsage_Returns0)
{
   _consoleMock->WriteLineMock.Expect();
   //
   const int exitCode = _cloudundancyProgram.Main(1, nullptr);
   //
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(CloudundancyArgs::CommandLineUsage));
   IS_ZERO(exitCode);
}

TEST(Main_ArgcIs2OrGreater_CallsTryCatchCallRunWithStringArgs_ReturnsExitCodeFromCallingRun)
{
   const vector<string> stringArgs = ArgcArgvToStringVectorMock.ReturnRandom();

   int tryCatchCallReturnValue = ZenUnit::Random<int>();
   _tryCatchCallerMock->TryCatchCallNonConstMemberFunctionMock.Return(tryCatchCallReturnValue);

   const int argc = 2;
   const string exePath = ZenUnit::Random<string>();
   const string commandLineArgument = ZenUnit::Random<string>();
   const char* const argv[] = { exePath.c_str(), commandLineArgument.c_str() };
   //
   const int exitCode = _cloudundancyProgram.Main(argc, const_cast<char**>(argv));
   //
   METALMOCK(ArgcArgvToStringVectorMock.CalledOnceWith(argc, const_cast<char**>(argv)));
   METALMOCK(_tryCatchCallerMock->TryCatchCallNonConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyProgram, &CloudundancyProgram::Run, stringArgs, &CloudundancyProgram::ExceptionHandler));
   ARE_EQUAL(tryCatchCallReturnValue, exitCode);
}

TEST2X2(Run_PrintsCommandLineAndStartTimeAndMachineName_ParsesArgs_NewsAndRunsSubProgram_PrintsEndTimeAndElapsedTime_ExitsWithSubProgramExitCode_WritesExitCodeInGreenIf0OtherwiseRed,
   int subProgramExitCode, Color expectedExitCodeLineColor,
   0, Color::Green,
   1, Color::Red,
   2, Color::Red)
{
   _stopwatchMock->StartMock.Expect();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();

   const string machineName = _environmentServiceMock->MachineNameMock.ReturnRandom();
   const string userName = _environmentServiceMock->UserNameMock.ReturnRandom();

   const string startTime = ZenUnit::Random<string>();
   const string endTime = ZenUnit::Random<string>();
   _watchMock->DateTimeNowMock.ReturnValues(startTime, endTime);

   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   _cloudundancyArgsParserMock->ParseStringArgsMock.Return(args);

   const string elapsedSeconds = ZenUnit::Random<string>();
   _stopwatchMock->StopAndGetElapsedSecondsMock.Return(elapsedSeconds);

   const shared_ptr<CloudundancySubProgramMock> cloudundancySubProgramMock = make_shared<CloudundancySubProgramMock>();
   cloudundancySubProgramMock->RunMock.Return(subProgramExitCode);
   _cloudundancySubProgramFactoryMock->NewCloudundancySubProgramMock.Return(cloudundancySubProgramMock);

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const int exitCode = _cloudundancyProgram.Run(stringArgs);
   //
   const string expectedSpaceJoinedArgs = Vector::Join(stringArgs, ' ');
   const string expectedRunningLine = "[Cloudundancy]     Running: " + expectedSpaceJoinedArgs;
   const string expectedMachineNameLine = "[Cloudundancy] MachineName: " + machineName;
   const string expectedUserNameLine = "[Cloudundancy]    UserName: " + userName;

   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_environmentServiceMock->MachineNameMock.CalledOnce());
   METALMOCK(_environmentServiceMock->UserNameMock.CalledOnce());
   METALMOCK(_watchMock->DateTimeNowMock.CalledNTimes(2));
   METALMOCK(_cloudundancyArgsParserMock->ParseStringArgsMock.CalledOnceWith(stringArgs));
   METALMOCK(_cloudundancySubProgramFactoryMock->NewCloudundancySubProgramMock.CalledOnceWith(args.programMode));
   METALMOCK(cloudundancySubProgramMock->RunMock.CalledOnceWith(args));
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(expectedRunningLine),
      string_view(expectedMachineNameLine),
      string_view(expectedUserNameLine),
      string_view("[Cloudundancy]   StartTime: " + startTime),
      string_view("[Cloudundancy]  EndTime: " + endTime),
      string_view("[Cloudundancy] Duration: " + elapsedSeconds + " seconds"),
   }));
   const string expectedExitCodeLine = "[Cloudundancy] ExitCode: " + to_string(subProgramExitCode);
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedExitCodeLine, expectedExitCodeLineColor));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   ARE_EQUAL(subProgramExitCode, exitCode);
}

// Private Functions

TEST(ExceptionHandler_PrintsExceptionClassNameAndMessage_Returns1)
{
   const string exceptionTypeNameAndMessage = GetExceptionClassNameAndMessageMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();

   const string endTime = _watchMock->DateTimeNowMock.ReturnRandom();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->WriteLineColorMock.Expect();

   const exception ex{};
   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const int exitCode = _cloudundancyProgram.ExceptionHandler(ex, stringArgs);
   //
   METALMOCK(GetExceptionClassNameAndMessageMock.CalledOnceWith(&ex));
   const string expectedFullExceptionErrorMessage =
      "\n[Cloudundancy]     Error: Exception thrown: " + exceptionTypeNameAndMessage;
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(expectedFullExceptionErrorMessage),
      string_view("[Cloudundancy]   EndTime: " + endTime),
      string_view("[Cloudundancy]  Duration: " + elapsedSeconds + " seconds")
   }));
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("[Cloudundancy]  ExitCode: 1", Color::Red));
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   ARE_EQUAL(1, exitCode);
}

RUN_TESTS(CloudundancyProgramTests)
