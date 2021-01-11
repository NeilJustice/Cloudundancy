import os
import platform
import sys
import unittest
from unittest.mock import call, patch
import docopt
from PyUtils import CMake, BuildAndInstallCPlusPlusProgram, Process, Random, UnitTester

testNames = [
'docstring__IsExpectedString_test',
'main__ValidArgs_CMakes_Builds_RunsTests_InstallsIfInstallArgSpecified_test',
'linux_cmake_build_test_install__RunCMakeThenRunsNinja_test',
'windows_cmake_build_test_install__RunsCMakeThenRunsMSBuild_test',
'optionally_install_program__RunsCMakeInstallTargetIfInstallArgSpecified_test'
]

class BuildAndInstallCPlusPlusProgramTests(unittest.TestCase):
   def setUp(self):
      self.solutionName = Random.string()
      self.cmakeGenerator = Random.string()
      self.cmakeArchitecture = Random.string()
      self.cmakeBuildType = Random.string()
      self.testsProjectName = Random.string()
      self.cmakeDefinitions = Random.string()
      self.doInstallProgram = Random.boolean()

   def docstring__IsExpectedString_test(self):
      self.assertEqual("""BuildAndInstallCPlusPlusProgram.py - Builds and installs a C++ progarm on Linux or Windows.

Usage: BuildAndInstallCPlusPlusProgram.py --solution-name=<String> --cmake-generator=<String> --cmake-architecture=<x64OrWin32> --cmake-build-type=<String> --tests-project-name=<String> [--cmake-definitions=<String>] (--install|--no-install)""",
      BuildAndInstallCPlusPlusProgram.__doc__)

   def main__ValidArgs_CMakes_Builds_RunsTests_InstallsIfInstallArgSpecified_test(self):
      @patch('builtins.print', spec_set=True)
      @patch('docopt.docopt', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('PyUtils.BuildAndInstallCPlusPlusProgram.linux_cmake_build_test_install', spec_set=True)
      @patch('PyUtils.BuildAndInstallCPlusPlusProgram.windows_cmake_build_test_install', spec_set=True)
      def testcase(platformSystem, trueExpectLinuxFalseExpectWindows, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem, trueExpectLinuxFalseExpectWindows}'):
            docopt.docopt.return_value =\
            {
               '--solution-name': self.solutionName,
               '--cmake-generator': self.cmakeGenerator,
               '--cmake-architecture': self.cmakeArchitecture,
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
            print.assert_called_once_with(expectedRunningSysArgvMessage)
            docopt.docopt.assert_called_once_with(BuildAndInstallCPlusPlusProgram.__doc__)
            platform.system.assert_called_once_with()
            if trueExpectLinuxFalseExpectWindows:
               BuildAndInstallCPlusPlusProgram.linux_cmake_build_test_install.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, self.doInstallProgram)
            else:
               BuildAndInstallCPlusPlusProgram.windows_cmake_build_test_install.assert_called_once_with(
                  self.solutionName, self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, self.doInstallProgram)
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   @patch('PyUtils.CMake.generate', spec_set=True)
   @patch('PyUtils.Process.fail_fast_run', spec_set=True)
   @patch('os.chdir', spec_set=True)
   @patch('PyUtils.BuildAndInstallCPlusPlusProgram.optionally_install_program', spec_set=True)
   def linux_cmake_build_test_install__RunCMakeThenRunsNinja_test(self, _1, _2, _3, _4):
      doInstallProgram = Random.boolean()
      #
      BuildAndInstallCPlusPlusProgram.linux_cmake_build_test_install(
         self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, doInstallProgram)
      #
      CMake.generate.assert_called_once_with(
         self.cmakeBuildType, self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.cmakeDefinitions, '..')
      expectedZenUnitTestsProgramCommand = f'{self.testsProjectName}/{self.testsProjectName} --test-runs=3 --random --exit-1-if-tests-skipped'
      self.assertEqual(2, len(Process.fail_fast_run.call_args_list))
      Process.fail_fast_run.assert_has_calls([
         call('ninja -v'),
         call(expectedZenUnitTestsProgramCommand)])
      os.chdir.assert_called_once_with('..')
      BuildAndInstallCPlusPlusProgram.optionally_install_program.assert_called_once_with(doInstallProgram, self.cmakeBuildType, self.cmakeBuildType)

   @patch('PyUtils.CMake.generate', spec_set=True)
   @patch('PyUtils.Process.fail_fast_run', spec_set=True)
   @patch('PyUtils.BuildAndInstallCPlusPlusProgram.optionally_install_program', spec_set=True)
   def windows_cmake_build_test_install__RunsCMakeThenRunsMSBuild_test(self, _1, _2, _3):
      doInstallProgram = Random.boolean()
      #
      BuildAndInstallCPlusPlusProgram.windows_cmake_build_test_install(
         self.solutionName, self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.testsProjectName, self.cmakeDefinitions, doInstallProgram)
      #
      CMake.generate.assert_called_once_with('.', self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.cmakeDefinitions, '.')
      expectedMSBuildCommand = f'MSBuild.exe {self.solutionName}.sln /p:Configuration={self.cmakeBuildType} /p:Platform=x64 /m'
      expectedZenUnitTestsProgramCommand = f'{self.testsProjectName}/{self.cmakeBuildType}/{self.testsProjectName}.exe --test-runs=3 --random --exit-1-if-tests-skipped'
      self.assertEqual(2, len(Process.fail_fast_run.call_args_list))
      Process.fail_fast_run.assert_has_calls([
         call(expectedMSBuildCommand),
         call(expectedZenUnitTestsProgramCommand)])
      BuildAndInstallCPlusPlusProgram.optionally_install_program.assert_called_once_with(doInstallProgram, '.', self.cmakeBuildType)

   def optionally_install_program__RunsCMakeInstallTargetIfInstallArgSpecified_test(self):
      @patch('PyUtils.Process.fail_fast_run', spec_set=True)
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
