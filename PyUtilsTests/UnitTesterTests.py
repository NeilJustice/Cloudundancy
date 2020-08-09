import unittest
from unittest.mock import patch, Mock, sentinel
from PyUtils import UnitTester, Random

specification = [
'test_run_tests_RunsTestCaseWithTextTestRunner'
]

class UnitTesterTests(unittest.TestCase):

   @patch('builtins.map', spec_set=True)
   @patch('unittest.TestSuite', spec_set=True)
   @patch('unittest.TextTestRunner', spec_set=True)
   def test_run_tests_RunsTestCaseWithTextTestRunner(self, _1, _2, _3):
      map.return_value = sentinel.testCaseMapObject
      unittest.TestSuite.return_value = Mock(spec=[''])
      textTestRunnerMock = Mock(spec=['run'])
      unittest.TextTestRunner.return_value = textTestRunnerMock
      testCaseName = Random.string()
      testNames = [Random.string(), Random.string()]
      #
      UnitTester.run_tests(testCaseName, testNames)
      #
      unittest.TextTestRunner.assert_called_once_with(verbosity=3)
      map.assert_called_once_with(testCaseName, testNames)
      unittest.TestSuite.assert_called_once_with(sentinel.testCaseMapObject)
      textTestRunnerMock.run.assert_called_once_with(unittest.TestSuite.return_value)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(UnitTesterTests, specification)
