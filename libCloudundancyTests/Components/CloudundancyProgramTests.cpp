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
METALMOCK_NONVOID1_STATIC_OR_FREE(string, _call_Type_GetExceptionClassNameAndMessage, const exception*)
METALMOCK_NONVOID2_STATIC_OR_FREE(vector<string>, _call_Vector_ArgcArgvToStringVector, int, char**)
// Function Callers
Utils::TryCatchCallerMock<CloudundancyProgram, const vector<string>&>* _tryCatchCallerMock = nullptr;
// Constant Components
CloudundancyArgsParserMock* _cloudundancyArgsParserMock = nullptr;
CloudundancySubProgramFactoryMock* _cloudundancySubProgramFactoryMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
Utils::EnvironmentServiceMock* _environmentServiceMock = nullptr;
Utils::WatchMock* _watchMock = nullptr;
// Mutable Components
Utils::StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyProgram._call_Type_GetExceptionClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(_call_Type_GetExceptionClassNameAndMessageMock);
   _cloudundancyProgram._call_Vector_ArgcArgvToStringVector = BIND_2ARG_METALMOCK_OBJECT(_call_Vector_ArgcArgvToStringVectorMock);
   // Function Callers
   _cloudundancyProgram._tryCatchCaller.reset(_tryCatchCallerMock = new Utils::TryCatchCallerMock<CloudundancyProgram, const vector<string>&>);
   // Constant Components
   _cloudundancyProgram._cloudundancyArgsParser.reset(_cloudundancyArgsParserMock = new CloudundancyArgsParserMock);
   _cloudundancyProgram._cloudundancySubProgramFactory.reset(_cloudundancySubProgramFactoryMock = new CloudundancySubProgramFactoryMock);
   _cloudundancyProgram._environmentService.reset(_environmentServiceMock = new Utils::EnvironmentServiceMock);
   _cloudundancyProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
   _cloudundancyProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _cloudundancyProgram._watch.reset(_watchMock = new Utils::WatchMock);
   // Mutable Components
   _cloudundancyProgram._stopwatch.reset(_stopwatchMock = new Utils::StopwatchMock);
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
   const vector<string> stringArgs = _call_Vector_ArgcArgvToStringVectorMock.ReturnRandom();

   int tryCatchCallReturnValue = ZenUnit::Random<int>();
   _tryCatchCallerMock->TryCatchCallNonConstMemberFunctionMock.Return(tryCatchCallReturnValue);

   const int argc = 2;
   const string exePath = ZenUnit::Random<string>();
   const string commandLineArgument = ZenUnit::Random<string>();
   const char* const argv[] = { exePath.c_str(), commandLineArgument.c_str() };
   //
   const int exitCode = _cloudundancyProgram.Main(argc, const_cast<char**>(argv));
   //
   METALMOCKTHEN(_call_Vector_ArgcArgvToStringVectorMock.CalledOnceWith(argc, const_cast<char**>(argv))).Then(
   METALMOCKTHEN(_tryCatchCallerMock->TryCatchCallNonConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyProgram, &CloudundancyProgram::Run, stringArgs, &CloudundancyProgram::ExceptionHandler)));
   ARE_EQUAL(tryCatchCallReturnValue, exitCode);
}

TEST2X2(Run_PrintsCommandLineAndStartTimeAndMachineName_ParsesArgs_NewsAndRunsSubProgram_PrintsEndTimeAndElapsedTime_ExitsWithSubProgramExitCode_WritesExitCodeInGreenIf0OtherwiseRed,
   int subProgramExitCode, Utils::Color expectedExitCodeLineColor,
   0, Utils::Color::Green,
   1, Utils::Color::Red,
   2, Utils::Color::Red)
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
   const string expectedExitCodeLine = "[Cloudundancy] ExitCode: " + to_string(subProgramExitCode);
   METALMOCK(_consoleMock->WriteLineMock.CalledNTimes(6));
   METALMOCK(_watchMock->DateTimeNowMock.CalledNTimes(2));

   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce()).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedRunningLine))).Then(
   METALMOCKTHEN(_environmentServiceMock->MachineNameMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedMachineNameLine))).Then(
   METALMOCKTHEN(_environmentServiceMock->UserNameMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedUserNameLine))).Then(
   METALMOCKTHEN(_watchMock->DateTimeNowMock.Called())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("[Cloudundancy]   StartTime: " + startTime))).Then(
   METALMOCKTHEN(_cloudundancyArgsParserMock->ParseStringArgsMock.CalledOnceWith(stringArgs))).Then(
   METALMOCKTHEN(_cloudundancySubProgramFactoryMock->NewCloudundancySubProgramMock.CalledOnceWith(args.programMode))).Then(
   METALMOCKTHEN(cloudundancySubProgramMock->RunMock.CalledOnceWith(args))).Then(

   METALMOCKTHEN(_watchMock->DateTimeNowMock.Called())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("[Cloudundancy]  EndTime: " + endTime))).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("[Cloudundancy] Duration: " + elapsedSeconds + " seconds"))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedExitCodeLine, expectedExitCodeLineColor)));
   ARE_EQUAL(subProgramExitCode, exitCode);
}

// Private Functions

TEST(ExceptionHandler_PrintsExceptionClassNameAndMessage_Returns1)
{
   const string exceptionTypeNameAndMessage = _call_Type_GetExceptionClassNameAndMessageMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();

   const string endTime = _watchMock->DateTimeNowMock.ReturnRandom();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->WriteLineColorMock.Expect();

   const exception ex{};
   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const int exitCode = _cloudundancyProgram.ExceptionHandler(ex, stringArgs);
   //
   const string expectedFullExceptionErrorMessage = "\n[Cloudundancy]     Error: Exception thrown: " + exceptionTypeNameAndMessage;
   METALMOCK(_consoleMock->WriteLineMock.CalledNTimes(3));
   METALMOCKTHEN(_call_Type_GetExceptionClassNameAndMessageMock.CalledOnceWith(&ex)).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedFullExceptionErrorMessage))).Then(
   METALMOCKTHEN(_watchMock->DateTimeNowMock.CalledOnce())).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("[Cloudundancy]   EndTime: " + endTime))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("[Cloudundancy]  Duration: " + elapsedSeconds + " seconds"))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith("[Cloudundancy]  ExitCode: 1", Utils::Color::Red)));
   ARE_EQUAL(1, exitCode);
}

RUN_TESTS(CloudundancyProgramTests)
