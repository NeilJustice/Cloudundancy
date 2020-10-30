#include "pch.h"
#include "libCloudundancy/Components/CloudundancyProgram.h"
#include "libCloudundancy/Utilities/Exception.h"
#include "libCloudundancy/Utilities/Vector.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancyTests/Components/Exception/MetalMock/TryCatchCallerMock.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyArgsParserMock.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyIniFileReaderMock.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyFileCopierMock.h"
#include "libCloudundancyTests/Components/SubPrograms/MetalMock/CloudundancySubProgramFactoryMock.h"
#include "libCloudundancyTests/Components/SubPrograms/MetalMock/CloudundancySubProgramMock.h"
#include "libCloudundancyTests/Components/Time/MetalMock/StopwatchMock.h"
#include "libCloudundancyTests/Components/Time/MetalMock/WatchMock.h"

TESTS(CloudundancyProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Main_CallsTryCatchCallRunWithStringArgs_ReturnsExitCode)
AFACT(Run_PrintsCommandLineAndStartTimeAndMachineName_ParsesArgs_NewsAndRunsSubProgram_PrintsEndTimeAndElapsedTime_ExitsWithSubProgramExitCode)
// Private Functions
AFACT(ExceptionHandler_PrintsExceptionClassNameAndMessage_Returns1)
EVIDENCE

CloudundancyProgram _cloudundancyProgram;
// Function Callers
METALMOCK_NONVOID2_STATIC(vector<string>, Vector, ArgcArgvToStringVector, int, char**)
METALMOCK_NONVOID1_STATIC(string, Exception, GetExceptionClassNameAndMessage, const exception*)
// Constant Components
CloudundancyArgsParserMock* _cloudundancyArgsParserMock = nullptr;
CloudundancySubProgramFactoryMock* _cloudundancySubProgramFactoryMock = nullptr;
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
TryCatchCallerMock<CloudundancyProgram, const vector<string>&>* _tryCatchCallerMock = nullptr;
WatchMock* _watchMock = nullptr;
// Mutable Components
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Callers
   _cloudundancyProgram._call_Exception_GetExceptionClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(GetExceptionClassNameAndMessageMock);
   _cloudundancyProgram._call_Vector_ArgcArgvToStringVector = BIND_2ARG_METALMOCK_OBJECT(ArgcArgvToStringVectorMock);
   // Constant Components
   _cloudundancyProgram._cloudundancyArgsParser.reset(_cloudundancyArgsParserMock = new CloudundancyArgsParserMock);
   _cloudundancyProgram._cloudundancySubProgramFactory.reset(_cloudundancySubProgramFactoryMock = new CloudundancySubProgramFactoryMock);
   _cloudundancyProgram._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _cloudundancyProgram._tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock<CloudundancyProgram, const vector<string>&>);
   _cloudundancyProgram._watch.reset(_watchMock = new WatchMock);
   // Mutable Components
   _cloudundancyProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyProgram cloudundancyProgram;
   // Function Callers
   STD_FUNCTION_TARGETS(Exception::GetExceptionClassNameAndMessage, cloudundancyProgram._call_Exception_GetExceptionClassNameAndMessage);
   STD_FUNCTION_TARGETS(Vector::ArgcArgvToStringVector, cloudundancyProgram._call_Vector_ArgcArgvToStringVector);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancyArgsParser);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancySubProgramFactory);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancyFileCopier);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._tryCatchCaller);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._watch);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._stopwatch);
}

TEST(Main_CallsTryCatchCallRunWithStringArgs_ReturnsExitCode)
{
   const vector<string> stringArgs = ArgcArgvToStringVectorMock.ReturnRandom();

   int tryCatchCallReturnValue = ZenUnit::Random<int>();
   _tryCatchCallerMock->TryCatchCallMock.Return(tryCatchCallReturnValue);

   const int argc = 2;
   const string exePath = ZenUnit::Random<string>();
   const string commandLineArgument = ZenUnit::Random<string>();
   const char* const argv[] = { exePath.c_str(), commandLineArgument.c_str() };
   //
   const int exitCode = _cloudundancyProgram.Main(argc, const_cast<char**>(argv));
   //
   METALMOCK(ArgcArgvToStringVectorMock.CalledOnceWith(argc, const_cast<char**>(argv)));
   METALMOCK(_tryCatchCallerMock->TryCatchCallMock.CalledOnceWith(
      &_cloudundancyProgram, &CloudundancyProgram::Run, stringArgs, &CloudundancyProgram::ExceptionHandler));
   ARE_EQUAL(tryCatchCallReturnValue, exitCode);
}

TEST(Run_PrintsCommandLineAndStartTimeAndMachineName_ParsesArgs_NewsAndRunsSubProgram_PrintsEndTimeAndElapsedTime_ExitsWithSubProgramExitCode)
{
   _stopwatchMock->StartMock.Expect();

   _consoleMock->WriteLineMock.Expect();

   const string startTime = _watchMock->DateTimeNowMock.ReturnRandom();

   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   _cloudundancyArgsParserMock->ParseStringArgsMock.Return(args);

   const string elapsedSeconds = ZenUnit::Random<string>();
   _stopwatchMock->StopAndGetElapsedSecondsMock.Return(elapsedSeconds);

   const shared_ptr<CloudundancySubProgramMock> cloudundancySubProgramMock = make_shared<CloudundancySubProgramMock>();
   const int subProgramExitCode = cloudundancySubProgramMock->RunMock.ReturnRandom();
   _cloudundancySubProgramFactoryMock->NewCloudundancySubProgramMock.Return(cloudundancySubProgramMock);

   const map<string, docopt::Value> docoptArgs;
   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const int exitCode = _cloudundancyProgram.Run(stringArgs);
   //
   const string expectedSpaceJoinedArgs = Vector::Join(stringArgs, ' ');
   const string expectedRunningMessage = "[Cloudundancy]   Running: " + expectedSpaceJoinedArgs;

   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   METALMOCK(_cloudundancyArgsParserMock->ParseStringArgsMock.CalledOnceWith(stringArgs));
   METALMOCK(_cloudundancySubProgramFactoryMock->NewCloudundancySubProgramMock.CalledOnceWith(args.programMode));
   METALMOCK(cloudundancySubProgramMock->RunMock.CalledOnceWith(args));
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(expectedRunningMessage),
      string_view("[Cloudundancy] StartTime: " + startTime),
      string_view("[Cloudundancy] OverallBackupResult: All non-ignored files and folders successfully copied to all destination folders."),
      string_view("[Cloudundancy]  OverallElapsedTime: " + elapsedSeconds + " seconds"),
      string_view("[Cloudundancy]            ExitCode: " + to_string(subProgramExitCode))
   }));
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

   const exception ex;
   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const int exitCode = _cloudundancyProgram.ExceptionHandler(ex, stringArgs);
   //
   METALMOCK(GetExceptionClassNameAndMessageMock.CalledOnceWith(&ex));
   const string expectedFullExceptionErrorMessage =
      "\n[Cloudundancy]       Error: Exception thrown: " + exceptionTypeNameAndMessage;
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(expectedFullExceptionErrorMessage),
      string_view("[Cloudundancy]     EndTime: " + endTime),
      string_view("[Cloudundancy] ElapsedTime: " + elapsedSeconds + " seconds"),
      string_view("[Cloudundancy]    ExitCode: 1")
   }));
   METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   ARE_EQUAL(1, exitCode);
}

RUN_TESTS(CloudundancyProgramTests)
