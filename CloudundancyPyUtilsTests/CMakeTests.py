import os
import platform
import unittest
from unittest.mock import patch
from CloudundancyPyUtils import CMake, UnitTester, Process, Random

testNames = [
'generate_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType_test'
]

class CMakeTests(unittest.TestCase):
   def setUp(self):
      self.cmakeFolderPath = Random.string()
      self.cmakeGenerator = Random.string()
      self.cmakeBuildType = Random.string()
      self.cmakeListsFolderPath = Random.string()

   def generate_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType_test(self):
      @patch('os.makedirs', spec_set=True)
      @patch('os.chdir', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('CloudundancyPyUtils.Process.fail_fast_run', spec_set=True)
      def testcase(platformSystem, cmakeDefinitions, expectedCMakeCommand, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem, cmakeDefinitions, expectedCMakeCommand}'):
            platform.system.return_value = platformSystem
            #
            CMake.generate(self.cmakeFolderPath, self.cmakeGenerator, self.cmakeBuildType, cmakeDefinitions, self.cmakeListsFolderPath)
            #
            os.makedirs.assert_called_once_with(self.cmakeFolderPath, exist_ok=True)
            os.chdir.assert_called_once_with(self.cmakeFolderPath)
            print.assert_called_once_with('Generating CMake in folder', self.cmakeFolderPath)
            Process.fail_fast_run.assert_called_once_with(expectedCMakeCommand)
      testcase('Linux', '',
         f'cmake -Werror=dev -G"{self.cmakeGenerator}" -DCMAKE_BUILD_TYPE={self.cmakeBuildType}  {self.cmakeListsFolderPath}')
      testcase('Linux', '-DAddressSanitizerMode=ON',
         f'cmake -Werror=dev -G"{self.cmakeGenerator}" -DCMAKE_BUILD_TYPE={self.cmakeBuildType} -DAddressSanitizerMode=ON {self.cmakeListsFolderPath}')
      testcase('linux', '',
         f'cmake -Werror=dev -G"{self.cmakeGenerator}"  {self.cmakeListsFolderPath}')
      testcase('Windows', '',
        f'cmake -Werror=dev -G"{self.cmakeGenerator}"  {self.cmakeListsFolderPath}')
      testcase('Windows', '-DCMAKE_INSTALL_PREFIX=C:/',
         f'cmake -Werror=dev -G"{self.cmakeGenerator}" -DCMAKE_INSTALL_PREFIX=C:/ {self.cmakeListsFolderPath}')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CMakeTests, testNames)
