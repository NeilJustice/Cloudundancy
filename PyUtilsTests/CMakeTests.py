import collections
import functools
import os
import platform
import unittest
from unittest.mock import patch
from unittest.mock import call
from PyUtils import CMake, File, UnitTester, Process, Random

testNames = [
'generate_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType_test',
'generate_in_folder_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType_test',
'generate_all_CallsGenerateOnRelativeFolderNamesContainingCMakeLists_test',
'delete_cmake_cache_file_then_cmake_DeletesCMakeCacheDotTxt_ThenCMakeGenerates_test',
'main_ArgvIsNotLength2OrArgv1IsNotDeleteCacheThenCMake_DoesNothing_test',
'main_ArgvIs2AndArgv1IsDeleteCacheThenCMake_DeletesCMakeCacheDotTxtThenCMakeGenerates_test'
]

class CMakeTests(unittest.TestCase):
   def setUp(self):
      self.cmakeFolderPath = Random.string()
      self.cmakeGenerator = Random.string()
      self.cmakeArchitecture = Random.string()
      self.cmakeBuildType = Random.string()
      self.cmakeListsFolderPath = Random.string()

   def generate_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType_test(self):
      @patch('os.makedirs', spec_set=True)
      @patch('os.chdir', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('PyUtils.Process.fail_fast_run', spec_set=True)
      def testcase(platformSystem, cmakeDefinitions, expectedCMakeCommand, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem, cmakeDefinitions, expectedCMakeCommand}'):
            platform.system.return_value = platformSystem
            #
            CMake.generate(self.cmakeFolderPath, self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, cmakeDefinitions, self.cmakeListsFolderPath)
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
         f'cmake -Werror=dev -G"{self.cmakeGenerator}" -A"{self.cmakeArchitecture}"  {self.cmakeListsFolderPath}')
      testcase('Windows', '',
        f'cmake -Werror=dev -G"{self.cmakeGenerator}" -A"{self.cmakeArchitecture}"  {self.cmakeListsFolderPath}')
      testcase('Windows', '-DCMAKE_INSTALL_PREFIX=C:/',
         f'cmake -Werror=dev -G"{self.cmakeGenerator}" -A"{self.cmakeArchitecture}" -DCMAKE_INSTALL_PREFIX=C:/ {self.cmakeListsFolderPath}')

   def generate_in_folder_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType_test(self):
      @patch('os.makedirs', spec_set=True)
      @patch('os.chdir', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('builtins.print', spec_set=True)
      @patch('PyUtils.Process.fail_fast_run', spec_set=True)
      def testcase(platformSystem, expectCMakeBuildTypeSpecified, _1, _2, _3, _4, _5):
         platform.system.return_value = platformSystem
         #
         CMake.generate_in_folder(self.cmakeFolderPath, self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.cmakeListsFolderPath)
         #
         os.makedirs.assert_called_once_with(self.cmakeFolderPath, exist_ok=True)
         os.chdir.assert_called_once_with(self.cmakeFolderPath)
         print.assert_called_once_with('Generating CMake in folder', self.cmakeFolderPath)
         if expectCMakeBuildTypeSpecified:
            expectedCMakeCommand = f'cmake -Werror=dev -G"{self.cmakeGenerator}" -DCMAKE_BUILD_TYPE={self.cmakeBuildType} {self.cmakeListsFolderPath}'
         else:
            expectedCMakeCommand = f'cmake -Werror=dev -G"{self.cmakeGenerator}" -A"{self.cmakeArchitecture}" {self.cmakeListsFolderPath}'
         Process.fail_fast_run.assert_called_once_with(expectedCMakeCommand)
      testcase('Linux', True)
      testcase('linux', False)
      testcase('Windows', False)

   @patch('functools.partial', spec_set=True)
   @patch('builtins.map', spec_set=True)
   @patch('collections.deque', spec_set=True)
   def generate_all_CallsGenerateOnRelativeFolderNamesContainingCMakeLists_test(self, _1, _2, _3):
      baseFolderPath = Random.string()
      folderNamesContainingCMakeLists = [Random.string(), Random.string()]
      osPathJoinPartial = Random.string()
      generateInFolderPartial = Random.string()
      functools.partial.side_effect = [osPathJoinPartial, generateInFolderPartial]

      folderPathsContainingCMakeLists = [Random.string(), Random.string()]

      mapObject = Random.string()
      map.side_effect = [folderPathsContainingCMakeLists, mapObject]
      #
      CMake.generate_all(baseFolderPath, folderNamesContainingCMakeLists)
      #
      self.assertEqual(2, len(functools.partial.call_args_list))
      functools.partial.assert_has_calls([
         call(os.path.join, baseFolderPath),
         call(CMake.generate_in_folder, generator='Visual Studio 16 2019', architecture='x64', buildType='N/A', cmakeListsFolderPath='.')])
      self.assertEqual(2, len(map.call_args_list))
      map.assert_has_calls([
         call(osPathJoinPartial, folderNamesContainingCMakeLists),
         call(generateInFolderPartial, folderPathsContainingCMakeLists)])
      collections.deque.assert_called_once_with(mapObject, maxlen=0)

   @patch('PyUtils.File.delete', spec_set=True)
   @patch('PyUtils.CMake.generate', spec_set=True)
   def delete_cmake_cache_file_then_cmake_DeletesCMakeCacheDotTxt_ThenCMakeGenerates_test(self, _1, _2):
      #
      CMake.delete_cmake_cache_file_then_cmake()
      #
      File.delete.assert_called_once_with('CMakeCache.txt')
      CMake.generate.assert_called_once_with('.', 'Visual Studio 16 2019', 'x64', '', '-DCMAKE_INSTALL_PREFIX=C:\\', '.')

   @patch('PyUtils.CMake.delete_cmake_cache_file_then_cmake', spec_set=True)
   def main_ArgvIsNotLength2OrArgv1IsNotDeleteCacheThenCMake_DoesNothing_test(self, _1):
      CMake.main([])
      CMake.main(['CMake.py'])
      CMake.main(['CMake.py', 'not_DeleteCacheThenCMake'])
      CMake.delete_cmake_cache_file_then_cmake.assert_not_called()

   @patch('PyUtils.CMake.delete_cmake_cache_file_then_cmake', spec_set=True)
   def main_ArgvIs2AndArgv1IsDeleteCacheThenCMake_DeletesCMakeCacheDotTxtThenCMakeGenerates_test(self, _1):
      CMake.main(['CMake.py', 'DeleteCacheThenCMake'])
      CMake.delete_cmake_cache_file_then_cmake.assert_called_once_with()

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CMakeTests, testNames)
