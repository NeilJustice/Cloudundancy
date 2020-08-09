import collections
import functools
import platform
import os
import shutil
import unittest
from unittest.mock import patch, Mock
import pathlib
from PyUtils import FileSystem, UnitTester, Random

testNames = [
'current_directory_name_ReturnsCurrentDirectoryName_test',
'copy_doth_and_dotcpp_files_test',
'get_all_filepaths_ReturnsAllFilePathsInAndBelowFolderPath_test',
'filepath_ends_with_doth_or_dotcpp_ReturnsTrueIfFilePathEndsWithDotHOrDotCppLowercase_test',
'remove_folder_if_exists_RemovesFolderIfItExists_test',
'copy_file_test',
'get_folderpaths_in_folder_ReturnsFolderPathsInFolder_test',
'install_copy_file_CopiesFileAndPrintsSourceAndDestFilePaths_test'
]

class FileSystemTests(unittest.TestCase):
   def setUp(self):
      self.sourceFilePath = Random.string()
      self.destFilePath = Random.string()
      self.sourceFolderPath = Random.string()
      self.destFolderPath = Random.string()

   def current_directory_name_ReturnsCurrentDirectoryName_test(self):
      @patch('os.getcwd', spec_set=True)
      def testcase(currentDirectoryPath, expectedCurrentDirectoryName, _1):
         with self.subTest(f'{currentDirectoryPath, expectedCurrentDirectoryName}'):
            os.getcwd.return_value = currentDirectoryPath
            #
            currentDirectoryName = FileSystem.current_directory_name()
            #
            self.assertEqual(expectedCurrentDirectoryName, currentDirectoryName)
      testcase('', '')
      testcase('a', 'a')
      if platform.system() == 'Linux':
         testcase('a/b', 'b') # pragma nocover
         testcase('a/b/c', 'c') # pragma nocover
      else:
         testcase(r'a\b', 'b') # pragma nocover
         testcase(r'a\b\c', 'c') # pragma nocover

   @patch('PyUtils.FileSystem.get_all_filepaths', spec_set=True)
   @patch('builtins.filter')
   @patch('functools.partial', spec_set=True)
   @patch('builtins.map', spec_set=True)
   @patch('collections.deque', spec_set=True)
   @patch('builtins.print', spec_set=True)
   def copy_doth_and_dotcpp_files_test(self, _1, _2, _3, _4, _5, _6):
      sourceFilePaths = [Random.string(), Random.string()]
      FileSystem.get_all_filepaths.return_value = sourceFilePaths
      sourceAndHeaderFilePaths = [Random.string(), Random.string()]
      filter.return_value = sourceAndHeaderFilePaths
      #
      FileSystem.copy_doth_and_dotcpp_files(self.sourceFolderPath, self.destFolderPath)
      #
      FileSystem.get_all_filepaths.assert_called_once_with(self.sourceFolderPath)
      filter.assert_called_once_with(FileSystem.filepath_ends_with_doth_or_dotcpp, sourceFilePaths)
      functools.partial.assert_called_once_with(FileSystem.copy_file, self.destFolderPath)
      map.assert_called_once_with(functools.partial.return_value, sourceAndHeaderFilePaths)
      collections.deque.assert_called_once_with(map.return_value, maxlen=0)
      print.assert_called_once_with('Copied .h and .cpp files recursively from folder',
         self.sourceFolderPath, 'to folder', self.destFolderPath)

   def get_all_filepaths_ReturnsAllFilePathsInAndBelowFolderPath_test(self): # pragma nocover
      @patch('os.walk', spec_set=True)
      def testcase(expectedFilePaths, oswalkReturnValue, _1):
         with self.subTest(f'{expectedFilePaths, oswalkReturnValue}'):
            os.walk.return_value = oswalkReturnValue
            folderPath = Random.string()
            #
            filePaths = FileSystem.get_all_filepaths(folderPath)
            #
            os.walk.assert_called_once_with(folderPath)
            self.assertEqual(expectedFilePaths, filePaths)
      if platform.system() == 'Windows':
         testcase([], [])
         testcase([r'.\a.txt'], [('.', [], ['a.txt'])])
         testcase([
            r'.\file1.bin',
            r'.\file2',
            r'.\folderB\b2.txt',
            r'.\folderB\b1.txt',
            r'.\folderA\a1.txt',
            r'.\folderA\a2.txt'
         ], [
            ('.', ['folderB', 'folderA'], ['file1.bin', 'file2']),
            (r'.\folderB', ['emptyfolder'], ['b2.txt', 'b1.txt']),
            (r'.\folderB/emptyfolder', [], []),
            (r'.\folderA', [], ['a1.txt', 'a2.txt'])
         ])
      else:
         testcase([], [])
         testcase(['./a.txt'], [('.', [], ['a.txt'])])
         testcase([
            './file1.bin',
            './file2',
            './folderB/b2.txt',
            './folderB/b1.txt',
            './folderA/a1.txt',
            './folderA/a2.txt'
         ], [
            ('.', ['folderB', 'folderA'], ['file1.bin', 'file2']),
            ('./folderB', ['emptyfolder'], ['b2.txt', 'b1.txt']),
            ('./folderB/emptyfolder', [], []),
            ('./folderA', [], ['a1.txt', 'a2.txt'])
         ])

   def filepath_ends_with_doth_or_dotcpp_ReturnsTrueIfFilePathEndsWithDotHOrDotCppLowercase_test(self):
      def testcase(expectedReturnValue, filePath):
         with self.subTest(f'{expectedReturnValue, filePath}'):
            self.assertEqual(expectedReturnValue, FileSystem.filepath_ends_with_doth_or_dotcpp(filePath))
      testcase(True, 'filename.h')
      testcase(True, '.h')
      testcase(True, 'filename.cpp')
      testcase(True, '.cpp')
      testcase(False, 'h')
      testcase(False, 'cpp')
      testcase(False, 'filename.H')
      testcase(False, 'filename.hpp')
      testcase(False, 'filename.CPP')
      testcase(False, 'filename.Cpp')

   @patch('os.path.join', spec_set=True)
   @patch('os.path.dirname', spec_set=True)
   @patch('os.makedirs', spec_set=True)
   @patch('shutil.copy', spec_set=True)
   def copy_file_test(self, _1, _2, _3, _4):
      os.path.join.return_value = self.destFilePath
      destFilePathDirName = Random.string()
      os.path.dirname.return_value = destFilePathDirName
      #
      FileSystem.copy_file(self.destFolderPath, self.sourceFilePath)
      #
      os.path.join.assert_called_once_with(self.destFolderPath, self.sourceFilePath)
      os.path.dirname.assert_called_once_with(self.destFilePath)
      os.makedirs.assert_called_once_with(destFilePathDirName, exist_ok=True)
      shutil.copy.assert_called_once_with(self.sourceFilePath, self.destFilePath)

   def remove_folder_if_exists_RemovesFolderIfItExists_test(self):
      @patch('os.path.exists', spec_set=True)
      @patch('shutil.rmtree', spec_set=True)
      def testcase(folderPathExists, expectRmtreeCall, _1, _2):
         with self.subTest(f'{folderPathExists, expectRmtreeCall}'):
            os.path.exists.return_value = folderPathExists
            folderPath = Random.string()
            #
            FileSystem.remove_folder_if_exists(folderPath)
            #
            os.path.exists.assert_called_once_with(folderPath)
            if expectRmtreeCall:
               shutil.rmtree.assert_called_once_with(folderPath)
            else:
               shutil.rmtree.assert_not_called()
      testcase(False, False)
      testcase(True, True)

   @patch('pathlib.Path', spec_set=True)
   def get_folderpaths_in_folder_ReturnsFolderPathsInFolder_test(self, _1):
      windowsFilePathA = Mock(spec=['is_dir'])
      windowsFilePathA.is_dir.return_value = False

      windowsFolderPathA = Mock(spec=['is_dir'])
      windowsFolderPathA.is_dir.return_value = True

      windowsFilePathB = Mock(spec=['is_dir'])
      windowsFilePathB.is_dir.return_value = False

      windowsFolderPathB = Mock(spec=['is_dir'])
      windowsFolderPathB.is_dir.return_value = True

      pathLibFolderPath = Mock(spec=['iterdir'])
      pathLibFolderPath.iterdir.return_value = [
         windowsFilePathA, windowsFolderPathA, windowsFilePathB, windowsFolderPathB]
      pathlib.Path.return_value = pathLibFolderPath

      folderPath = Random.string()
      #
      folderPathsInFolder = FileSystem.get_folderpaths_in_folder(folderPath)
      #
      pathlib.Path.assert_called_once_with(folderPath)
      windowsFilePathA.is_dir.assert_called_once_with()
      windowsFolderPathA.is_dir.assert_called_once_with()
      windowsFilePathB.is_dir.assert_called_once_with()
      windowsFolderPathB.is_dir.assert_called_once_with()
      pathLibFolderPath.iterdir.assert_called_once_with()
      expectedWindowsFolderPaths = [windowsFolderPathA, windowsFolderPathB]
      self.assertEqual(expectedWindowsFolderPaths, folderPathsInFolder)

   @patch('shutil.copyfile', spec_set=True)
   @patch('builtins.print', spec_set=True)
   def install_copy_file_CopiesFileAndPrintsSourceAndDestFilePaths_test(self, _1, _2):
      #
      FileSystem.install_copy_file(self.sourceFilePath, self.destFilePath)
      #
      shutil.copyfile.assert_called_once_with(self.sourceFilePath, self.destFilePath)
      print.assert_called_once_with('Copied', self.sourceFilePath, 'to', self.destFilePath)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(FileSystemTests, testNames)
