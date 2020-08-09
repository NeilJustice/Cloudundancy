#include "pch.h"
#include "libCloudundancy/Components/CloudundancyProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/SubPrograms/MetalMock/CloudundancySubProgramFactoryMock.h"
#include "libCloudundancyTests/Components/SubPrograms/MetalMock/CloudundancySubProgramMock.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyArgsParserMock.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyIniFileReaderMock.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyFileCopierMock.h"

TESTS(CloudundancyProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Main_CallsTryCatchCallRunWithStringArgs_ReturnsExitCode)
AFACT(Run_ParsesArgsWithDocopt_CopiesCode_CallsCodeFolderBackupperIfBackupCodeFolderMode_Returns0)
// Private Functions
AFACT(ExceptionHandler_PrintsExceptionGetExceptionClassNameAndMessage_Returns1)
EVIDENCE

CloudundancyProgram _cloudundancyProgram;
METALMOCK_NONVOID2_STATIC(vector<string>, Vector, ArgcArgvToStringVector, int, char**)
METALMOCK_NONVOID1_STATIC(string, Exception, GetExceptionClassNameAndMessage, const exception*)
CloudundancyArgsParserMock* _cloudundancyArgsParserMock = nullptr;
CloudundancySubProgramFactoryMock* _cloudundancySubProgramFactoryMock = nullptr;
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
TryCatchCallerMock<CloudundancyProgram, const vector<string>&>* _tryCatchCallerMock = nullptr;
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   _cloudundancyProgram._call_Exception_GetExceptionClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(GetExceptionClassNameAndMessageMock);
   _cloudundancyProgram._call_Vector_ArgcArgvToStringVector = BIND_2ARG_METALMOCK_OBJECT(ArgcArgvToStringVectorMock);
   _cloudundancyProgram._cloudundancyArgsParser.reset(_cloudundancyArgsParserMock = new CloudundancyArgsParserMock);
   _cloudundancyProgram._cloudundancySubProgramFactory.reset(_cloudundancySubProgramFactoryMock = new CloudundancySubProgramFactoryMock);
   _cloudundancyProgram._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _cloudundancyProgram._tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock<CloudundancyProgram, const vector<string>&>);
   _cloudundancyProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyProgram cloudundancyProgram;
   STD_FUNCTION_TARGETS(Exception::GetExceptionClassNameAndMessage, cloudundancyProgram._call_Exception_GetExceptionClassNameAndMessage);
   STD_FUNCTION_TARGETS(Vector::ArgcArgvToStringVector, cloudundancyProgram._call_Vector_ArgcArgvToStringVector);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancyArgsParser);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancySubProgramFactory);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._cloudundancyFileCopier);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._tryCatchCaller);
   DELETE_TO_ASSERT_NEWED(cloudundancyProgram._stopwatch);
}

TEST(Main_CallsTryCatchCallRunWithStringArgs_ReturnsExitCode)
{
   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   ArgcArgvToStringVectorMock.Return(stringArgs);

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

TEST(Run_ParsesArgsWithDocopt_CopiesCode_CallsCodeFolderBackupperIfBackupCodeFolderMode_Returns0)
{
   _consoleMock->WriteLineMock.Expect();

   _stopwatchMock->StartMock.Expect();

   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   _cloudundancyArgsParserMock->ParseStringArgsMock.Return(args);

   const string elapsedSeconds = ZenUnit::Random<string>();
   _stopwatchMock->StopAndGetElapsedSecondsMock.Return(elapsedSeconds);

   const shared_ptr<CloudundancySubProgramMock> cloudundancySubProgramMock = make_shared<CloudundancySubProgramMock>();
   cloudundancySubProgramMock->RunMock.Expect();
   _cloudundancySubProgramFactoryMock->NewCloudundancySubProgramMock.Return(cloudundancySubProgramMock);

   const map<string, docopt::Value> docoptArgs;
   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const int exitCode = _cloudundancyProgram.Run(stringArgs);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   const string expectedSpaceJoinedArgs = Vector::Join(stringArgs, ' ');
   const string expectedRunningMessage = "[Cloudundancy] Running: " + expectedSpaceJoinedArgs;
   METALMOCK(_cloudundancyArgsParserMock->ParseStringArgsMock.CalledOnceWith(stringArgs));
   METALMOCK(_cloudundancySubProgramFactoryMock->NewCloudundancySubProgramMock.CalledOnceWith(args.programMode));
   METALMOCK(cloudundancySubProgramMock->RunMock.CalledOnceWith(args));
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(expectedRunningMessage),
      string_view("[Cloudundancy] OverallBackupResult: All non-ignored files and folders successfully copied to all destination folders."),
      string_view("[Cloudundancy]  OverallElapsedTime: " + elapsedSeconds + " seconds"),
      string_view("[Cloudundancy]            ExitCode: 0")
   }));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   ARE_EQUAL(0, exitCode);
}

// Private Functions

TEST(ExceptionHandler_PrintsExceptionGetExceptionClassNameAndMessage_Returns1)
{
   const string exceptionTypeNameAndMessage = GetExceptionClassNameAndMessageMock.ReturnRandom();
   _consoleMock->WriteLineMock.Expect();
   const exception ex;
   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const int exitCode = _cloudundancyProgram.ExceptionHandler(ex, stringArgs);
   //
   METALMOCK(GetExceptionClassNameAndMessageMock.CalledOnceWith(&ex));
   const string expectedFullExceptionErrorMessage = "\n[Cloudundancy] Error: Exception thrown: " + exceptionTypeNameAndMessage;
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(expectedFullExceptionErrorMessage),
      string_view("[Cloudundancy] ExitCode: 1")
   }));
   ARE_EQUAL(1, exitCode);
}

RUN_TESTS(CloudundancyProgramTests)
