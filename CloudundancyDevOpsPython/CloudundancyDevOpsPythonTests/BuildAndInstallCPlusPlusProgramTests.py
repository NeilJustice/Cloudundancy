import os
import platform
import sys
import unittest
from unittest.mock import call, patch
import docopt
from CloudundancyDevOpsPython import CMake, BuildAndInstallCPlusPlusProgram, Process
from CloudundancyDevOpsPythonTests import Random, UnitTester

testNames = [
'test_docstring__IsExpectedString',
'test_main__ValidArgs_CMakes_Builds_RunsTests_InstallsIfInstallArgSpecified',
'test_linux_cmake_build_test_install__RunCMakeThenRunsNinja',
'test_windows_cmake_build_test_install__RunsCMakeThenRunsMSBuild',
'test_optionally_install_program__RunsCMakeInstallTargetIfInstallArgSpecified'
]

class BuildAndInstallCPlusPlusProgramTests(unittest.TestCase):
   def setUp(self):
      self.solutionName = Random.string()
      self.cmakeGenerator = Random.string()
      self.cmakeBuildType = Random.string()
      self.testsProjectName = Random.string()
      self.cmakeDefinitions = Random.string()
      self.doInstallProgram = Random.boolean()

   def test_docstring__IsExpectedString(self):
      self.assertEqual("""BuildAndInstallCPlusPlusProgram.py - Builds and installs a C++ program on Linux or Windows.

Usage: BuildAndInstallCPlusPlusProgram.py --solution-name=<String> --cmake-generator=<String> --cmake-build-type=<String> --tests-project-name=<String> [--cmake-definitions=<String>] (--install|--no-install)""",
      BuildAndInstallCPlusPlusProgram.__doc__)

   def test_main__ValidArgs_CMakes_Builds_RunsTests_InstallsIfInstallArgSpecified(self):
      @patch('docopt.docopt', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('CloudundancyDevOpsPython.BuildAndInstallCPlusPlusProgram.linux_cmake_build_test_install', spec_set=True)
      @patch('CloudundancyDevOpsPython.BuildAndInstallCPlusPlusProgram.windows_cmake_build_test_install', spec_set=True)
      @patch('builtins.print', spec_set=True)
      def testcase(platformSystem, trueExpectLinuxFalseExpectWindows, printMock, _1, _2, _3, _4):
         with self.subTest(f'{platformSystem, trueExpectLinuxFalseExpectWindows}'):
            docopt.docopt.return_value =\
            {
               '--solution-name': self.solutionName,
               '--cmake-generator': self.cmakeGenerator,
               '--cmake-build-type': self.cmakeBuildType,
               '--tests-project-name': self.testsProjectName,
               '--cmake-definitions': self.cmakeDefinitions,
               '--install': self.doInstallProgram
            }
            platform.system.return_value = platformSystem
            #
            BuildAndInstallCPlusPlusProgram.main()
            #
            expectedRunningSysArgvMessage = f'Running {sys.argv}\n'
            printMock.assert_called_once_with(expectedRunningSysArgvMessage)
            docopt.docopt.assert_called_once_with(BuildAndInstallCPlusPlusProgram.__doc__)
            platform.system.assert_called_once_with()
            if trueExpectLinuxFalseExpectWindows:
               BuildAndInstallCPlusPlusProgram.linux_cmake_build_test_install.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, self.doInstallProgram)
            else:
               BuildAndInstallCPlusPlusProgram.windows_cmake_build_test_install.assert_called_once_with(
                  self.solutionName, self.cmakeGenerator, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, self.doInstallProgram)
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   @patch('CloudundancyDevOpsPython.CMake.generate', spec_set=True)
   @patch('CloudundancyDevOpsPython.Process.fail_fast_run', spec_set=True)
   @patch('os.chdir', spec_set=True)
   @patch('CloudundancyDevOpsPython.BuildAndInstallCPlusPlusProgram.optionally_install_program', spec_set=True)
   def test_linux_cmake_build_test_install__RunCMakeThenRunsNinja(self, _1, _2, _3, _4):
      doInstallProgram = Random.boolean()
      #
      BuildAndInstallCPlusPlusProgram.linux_cmake_build_test_install(
         self.cmakeGenerator, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, doInstallProgram)
      #
      CMake.generate.assert_called_once_with(self.cmakeBuildType, self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, '..')
      expectedZenUnitTestsProgramCommand = f'{self.testsProjectName}/{self.testsProjectName} --test-runs=2 --random --max-test-milliseconds=200 --exit-1-if-tests-skipped'
      self.assertEqual(2, len(Process.fail_fast_run.call_args_list))
      Process.fail_fast_run.assert_has_calls([
         call('ninja -v'),
         call(expectedZenUnitTestsProgramCommand)])
      os.chdir.assert_called_once_with('..')
      BuildAndInstallCPlusPlusProgram.optionally_install_program.assert_called_once_with(doInstallProgram, self.cmakeBuildType, self.cmakeBuildType)

   @patch('CloudundancyDevOpsPython.CMake.generate', spec_set=True)
   @patch('CloudundancyDevOpsPython.Process.fail_fast_run', spec_set=True)
   @patch('CloudundancyDevOpsPython.BuildAndInstallCPlusPlusProgram.optionally_install_program', spec_set=True)
   def test_windows_cmake_build_test_install__RunsCMakeThenRunsMSBuild(self, _1, _2, _3):
      doInstallProgram = Random.boolean()
      #
      BuildAndInstallCPlusPlusProgram.windows_cmake_build_test_install(
         self.solutionName, self.cmakeGenerator, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, doInstallProgram)
      #
      CMake.generate.assert_called_once_with('.', self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, '.')
      expectedMSBuildCommand = f'MSBuild.exe {self.solutionName}.sln /p:Configuration={self.cmakeBuildType} /p:Platform=x64 /m'
      expectedZenUnitTestsProgramCommand = f'{self.testsProjectName}/{self.cmakeBuildType}/{self.testsProjectName}.exe --test-runs=2 --random --max-test-milliseconds=200 --exit-1-if-tests-skipped'
      self.assertEqual(2, len(Process.fail_fast_run.call_args_list))
      Process.fail_fast_run.assert_has_calls([
         call(expectedMSBuildCommand),
         call(expectedZenUnitTestsProgramCommand)])
      BuildAndInstallCPlusPlusProgram.optionally_install_program.assert_called_once_with(doInstallProgram, '.', self.cmakeBuildType)

   def test_optionally_install_program__RunsCMakeInstallTargetIfInstallArgSpecified(self):
      @patch('CloudundancyDevOpsPython.Process.fail_fast_run', spec_set=True)
      def testcase(doInstallProgram, expectRunCMake, _1):
         with self.subTest(f'{doInstallProgram, expectRunCMake}'):
            cmakeBuildArgument = Random.string()
            #
            BuildAndInstallCPlusPlusProgram.optionally_install_program(doInstallProgram, cmakeBuildArgument, self.cmakeBuildType)
            #
            if expectRunCMake:
               expectedCMakeBuildCommand = f'cmake --build {cmakeBuildArgument} --target install --config {self.cmakeBuildType}'
               Process.fail_fast_run.assert_called_once_with(expectedCMakeBuildCommand)
            else:
               Process.fail_fast_run.assert_not_called()
      testcase(True, True)
      testcase(False, False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildAndInstallCPlusPlusProgramTests, testNames)
