import unittest

def run_tests(testCaseType, testNames):
   testCaseMapObject = map(testCaseType, testNames)
   testSuite = unittest.TestSuite(testCaseMapObject)
   textTestRunner = unittest.TextTestRunner(verbosity=3)
   textTestRunner.run(testSuite)
