import unittest
from typing import Any

def run_tests(testCaseType: Any, testNames: list) -> None:
   testCaseMapObject = map(testCaseType, testNames)
   testSuite = unittest.TestSuite(testCaseMapObject)
   textTestRunner = unittest.TextTestRunner(verbosity=3)
   textTestRunner.run(testSuite)
