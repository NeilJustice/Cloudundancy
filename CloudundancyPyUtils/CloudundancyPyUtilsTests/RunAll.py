import sys
import nose

noseConfig = nose.config.Config()
noseConfig.testMatchPat = 'Tests|_test|test_'
noseConfig.verbosity = 3
allTestsPassed = nose.run(config=noseConfig)
sys.exit(0 if allTestsPassed else 1)
