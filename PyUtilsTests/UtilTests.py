import os
import pprint
import sys
import unittest
from unittest.mock import patch
from unittest.mock import call
from PyUtils import UnitTester, Util, Random

testNames = [
'code_folder_join_ReturnsHomeFolderCodeFolderSpecifiedFolder_test',
'home_folder_join_test',
'pretty_print_Callspprintpprint_test',
'print_and_input_PrintsMessageThenCallsInput_test',
'print_and_exit_PrintsMessageThenCallsExitWithExitCode_test'
]

class UtilTests(unittest.TestCase):
   def setUp(self):
      self.message = Random.string()

   @patch('os.path.expanduser', spec_set=True)
   @patch('os.path.join', spec_set=True)
   def code_folder_join_ReturnsHomeFolderCodeFolderSpecifiedFolder_test(self, _1, _2):
      homeFolderPath = Random.string()
      os.path.expanduser.return_value = homeFolderPath
      codeFolderPath = Random.string()
      joinedCodeFolderPath = Random.string()
      os.path.join.side_effect = [codeFolderPath, joinedCodeFolderPath]
      folderPath = Random.string()
      #
      joinedCodeFolderPath = Util.code_folder_join(folderPath)
      #
      os.path.expanduser.assert_called_once_with('~')
      self.assertEqual(2, len(os.path.join.call_args_list))
      os.path.join.assert_has_calls([
         call(homeFolderPath, 'Code'),
         call(codeFolderPath, folderPath)])
      self.assertEqual(joinedCodeFolderPath, joinedCodeFolderPath)

   @patch('os.path.expanduser', spec_set=True)
   @patch('os.path.join', spec_set=True)
   def home_folder_join_test(self, _1, _2):
      homeFolderPath = Random.string()
      os.path.expanduser.return_value = homeFolderPath
      joinedHomeFolderPath = Random.string()
      os.path.join.return_value = joinedHomeFolderPath
      folderPath = Random.string()
      fileName = Random.string()
      #
      joinedHomeFolderPath = Util.home_folder_join(folderPath, fileName)
      #
      os.path.expanduser.assert_called_once_with('~')
      os.path.join.assert_called_once_with(homeFolderPath, folderPath, fileName)
      self.assertEqual(joinedHomeFolderPath, joinedHomeFolderPath)

   @patch('pprint.pprint', spec_set=True)
   def pretty_print_Callspprintpprint_test(self, _1):
      value = { Random.integer(), Random.integer() }
      #
      Util.pretty_print(value)
      #
      pprint.pprint.assert_called_once_with(value)

   @patch('builtins.print', spec_set=True)
   @patch('builtins.input', spec_set=True)
   def print_and_input_PrintsMessageThenCallsInput_test(self, _1, _2):
      #
      Util.print_and_input(self.message)
      #
      print.assert_called_once_with(self.message)
      input.assert_called_once_with()

   @patch('builtins.print', spec_set=True)
   @patch('sys.exit', spec_set=True)
   def print_and_exit_PrintsMessageThenCallsExitWithExitCode_test(self, _1, _2):
      exitCode = Random.integer()
      #
      Util.print_and_exit(self.message, exitCode)
      #
      print.assert_called_once_with(self.message)
      sys.exit.assert_called_once_with(exitCode)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(UtilTests, testNames)
