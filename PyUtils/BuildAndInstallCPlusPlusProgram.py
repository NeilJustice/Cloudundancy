"""BuildAndInstallCPlusPlusProgram.py - Builds and installs a C++ progarm on Linux or Windows.

Usage: BuildAndInstallCPlusPlusProgram.py --solution-name=<String> --cmake-generator=<String> --cmake-architecture=<x64OrWin32> --cmake-build-type=<String> --tests-project-name=<String> [--cmake-definitions=<String>] (--install|--no-install)"""
import os
import platform
import sys
import docopt
sys.path.append('.') # Jenkins
from PyUtils import CMake, Process

def linux_cmake_build_test_install(cmakeGenerator, cmakeArchitecture, cmakeBuildType, testsProjectName, cmakeDefinitions, doInstallProgram):
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeArchitecture, cmakeBuildType, cmakeDefinitions, '..')

   Process.fail_fast_run('ninja -v')

   zenUnitTestsProgramCommand = f'{testsProjectName}/{testsProjectName} --test-runs=3 --random-test-ordering --exit-1-if-tests-skipped'
   Process.fail_fast_run(zenUnitTestsProgramCommand)

   os.chdir('..')
   optionally_install_program(doInstallProgram, cmakeBuildType, cmakeBuildType)

def windows_cmake_build_test_install(solutionName, cmakeGenerator, cmakeArchitecture, cmakeBuildType, testsProjectName, cmakeDefinitions, doInstallProgram):
   CMake.generate('.', cmakeGenerator, cmakeArchitecture, cmakeBuildType, cmakeDefinitions, '.')

   msbuildCommand = f'MSBuild.exe {solutionName}.sln /p:Configuration={cmakeBuildType} /p:Platform=x64 /m'
   Process.fail_fast_run(msbuildCommand)

   zenUnitTestsProgramCommand = f'{testsProjectName}/{cmakeBuildType}/{testsProjectName}.exe --test-runs=3 --random-test-ordering --exit-1-if-tests-skipped'
   Process.fail_fast_run(zenUnitTestsProgramCommand)

   optionally_install_program(doInstallProgram, '.', cmakeBuildType)

def optionally_install_program(doInstallProgram, cmakeBuildArgument, cmakeBuildType):
   if doInstallProgram:
      cmakeInstallCommand = f'cmake --build {cmakeBuildArgument} --target install --config {cmakeBuildType}'
      Process.fail_fast_run(cmakeInstallCommand)

def main():
   runningSysArgvMessage = f'Running {sys.argv}\n'
   print(runningSysArgvMessage)
   arguments = docopt.docopt(__doc__)
   cmakeGenerator = arguments['--cmake-generator']
   cmakeArchitecture = arguments['--cmake-architecture']
   cmakeBuildType = arguments['--cmake-build-type']
   testsProjectName = arguments['--tests-project-name']
   solutionName = arguments['--solution-name']
   cmakeDefinitions = arguments['--cmake-definitions']
   doInstallProgram = arguments['--install']
   platformSystem = platform.system()
   if platformSystem.casefold() == 'linux':
      linux_cmake_build_test_install(cmakeGenerator, cmakeArchitecture, cmakeBuildType, testsProjectName, cmakeDefinitions, doInstallProgram)
   else:
      windows_cmake_build_test_install(solutionName, cmakeGenerator, cmakeArchitecture, cmakeBuildType, testsProjectName, cmakeDefinitions, doInstallProgram)

if __name__ == "__main__": # pragma nocover
   main()

# --solution-name=Cloudundancy --cmake-generator="Visual Studio 16 2019" --cmake-architecture="x64" --cmake-build-type=Debug --tests-project=libCloudundancyTests --no-install
# Working directory: C:\Code\Cloudundancy
