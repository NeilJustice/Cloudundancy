import os
import unittest
from unittest.mock import patch
from PyUtils import FileSystem, Install, UnitTester, Util, Random

testNames = [
'binary_CopiesConfigurationExeToLibFolder_test'
]

class InstallTests(unittest.TestCase):
   def setUp(self):
      self.solutionDirectory = Random.string()
      self.configuration = Random.string()
      self.projectName = Random.string()
      self.sourceFilePath = Random.string()
      self.destFilePath = Random.string()

   @patch('os.getcwd', spec_set=True)
   @patch('os.path.join', spec_set=True)
   @patch('PyUtils.Util.home_folder_join', spec_set=True)
   @patch('PyUtils.FileSystem.install_copy_file', spec_set=True)
   def binary_CopiesConfigurationExeToLibFolder_test(self, _1, _2, _3, _4):
      os.getcwd.return_value = self.solutionDirectory
      os.path.join.return_value = self.sourceFilePath
      Util.home_folder_join.return_value = self.destFilePath
      #
      Install.binary(self.projectName, self.configuration)
      #
      os.getcwd.assert_called_once_with()
      os.path.join.assert_called_once_with(
         self.solutionDirectory, self.projectName, self.configuration, self.projectName + '.exe')
      Util.home_folder_join.assert_called_once_with('bin', self.projectName + 'Installed.exe')
      FileSystem.install_copy_file.assert_called_once_with(self.sourceFilePath, self.destFilePath)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(InstallTests, testNames)
