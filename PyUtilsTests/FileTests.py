import os
import unittest
from unittest.mock import call, mock_open, patch
from PyUtils import File, UnitTester, Random

testNames = [
'read_text_ReadsFileText_test',
'read_lines_ReadsFileLines_test',
'write_text_WritesFileWithText_test',
'write_lines_CreatesContainingDirectory_WritesFileWithLines_test',
'delete_RemovesFileIfItExists_test'
]

class FileTests(unittest.TestCase):
   def setUp(self):
      self.filePath = Random.string()

   @patch('builtins.open', spec_set=True)
   def read_text_ReadsFileText_test(self, openMock):
      readData = Random.string()
      fileMock = mock_open(openMock, read_data=readData)
      #
      fileText = File.read_text(self.filePath)
      #
      fileMock.assert_has_calls([
         call(self.filePath, 'r'),
         call().__enter__(),
         call().read(),
         call().__exit__(None, None, None)])
      self.assertEqual(readData, fileText)

   @patch('builtins.open', spec_set=True)
   def read_lines_ReadsFileLines_test(self, openMock):
      line1 = Random.string()
      line2 = Random.string()
      readData = line1 + '\n' + line2
      fileMock = mock_open(openMock, read_data=readData)
      #
      fileText = File.read_lines(self.filePath)
      #
      fileMock.assert_has_calls([
         call(self.filePath, 'r'),
         call().__enter__(),
         call().readlines(),
         call().__exit__(None, None, None)])
      self.assertEqual([line1 + '\n', line2], fileText)

   @patch('builtins.open', spec_set=True)
   def write_text_WritesFileWithText_test(self, openMock):
      fileMock = mock_open(openMock)
      text = Random.string()
      #
      File.write_text(self.filePath, text)
      #
      fileMock.assert_has_calls([
         call(self.filePath, 'w'),
         call().__enter__(),
         call().write(text),
         call().__exit__(None, None, None)])

   @patch('os.path.dirname', spec_set=True)
   @patch('os.makedirs', spec_set=True)
   @patch('builtins.open', spec_set=True)
   def write_lines_CreatesContainingDirectory_WritesFileWithLines_test(self, openMock, _2, _3):
      dirName = Random.string()
      os.path.dirname.return_value = dirName
      fileMock = mock_open(openMock)
      line1 = Random.string()
      line2 = Random.string()
      lines = [line1, line2]
      #
      File.write_lines(self.filePath, lines)
      #
      os.path.dirname.assert_called_once_with(self.filePath)
      os.makedirs.assert_called_once_with(dirName, exist_ok=True)
      fileMock.assert_has_calls([
         call(self.filePath, 'w'),
         call().__enter__(),
         call().writelines([line1 + '\n', line2 + '\n']),
         call().__exit__(None, None, None)])

   def delete_RemovesFileIfItExists_test(self):
      @patch('os.path.exists', spec_set=True)
      @patch('os.remove', spec_set=True)
      def testcase(filePathExists, expectRemoveCall, _1, _2):
         with self.subTest(f'{filePathExists, expectRemoveCall}'):
            os.path.exists.return_value = filePathExists
            #
            File.delete(self.filePath)
            #
            os.path.exists.assert_called_once_with(self.filePath)
            if expectRemoveCall:
               os.remove.assert_called_once_with(self.filePath)
            else:
               os.remove.assert_not_called()
      testcase(False, False)
      testcase(True, True)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(FileTests, testNames)
