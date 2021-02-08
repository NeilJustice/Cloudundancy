import os
import platform
import unittest
from unittest.mock import patch
from CloudundancyPyUtils import CMake, File, UnitTester, Process, Random

testNames = [
'generate_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType_test',
'delete_cmake_cache_file_then_cmake_DeletesCMakeCacheDotTxt_ThenCMakeGenerates_test',
'main_ArgvIsNotLength2OrArgv1IsNotDeleteCacheThenCMake_DoesNothing_test',
'main_ArgvIs2AndArgv1IsDeleteCacheThenCMake_DeletesCMakeCacheDotTxtThenCMakeGenerates_test'
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

   @patch('CloudundancyPyUtils.File.delete', spec_set=True)
   @patch('CloudundancyPyUtils.CMake.generate', spec_set=True)
   def delete_cmake_cache_file_then_cmake_DeletesCMakeCacheDotTxt_ThenCMakeGenerates_test(self, _1, _2):
      #
      CMake.delete_cmake_cache_file_then_cmake()
      #
      File.delete.assert_called_once_with('CMakeCache.txt')
      CMake.generate.assert_called_once_with('.', 'Visual Studio 16 2019', '', '-DCMAKE_INSTALL_PREFIX=C:\\', '.')

   @patch('CloudundancyPyUtils.CMake.delete_cmake_cache_file_then_cmake', spec_set=True)
   def main_ArgvIsNotLength2OrArgv1IsNotDeleteCacheThenCMake_DoesNothing_test(self, _1):
      CMake.main([])
      CMake.main(['CMake.py'])
      CMake.main(['CMake.py', 'not_DeleteCacheThenCMake'])
      CMake.delete_cmake_cache_file_then_cmake.assert_not_called()

   @patch('CloudundancyPyUtils.CMake.delete_cmake_cache_file_then_cmake', spec_set=True)
   def main_ArgvIs2AndArgv1IsDeleteCacheThenCMake_DeletesCMakeCacheDotTxtThenCMakeGenerates_test(self, _1):
      CMake.main(['CMake.py', 'DeleteCacheThenCMake'])
      CMake.delete_cmake_cache_file_then_cmake.assert_called_once_with()

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CMakeTests, testNames)
