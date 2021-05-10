Set-PSDebug -Trace 1

$env:PYTHONPATH="."
python.exe CloudundancyDevOpsPython\MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=CloudundancyDevOpsPythonTests/RunAllWithCoverage.py

Set-PSDebug -Trace 0
exit $LastExitCode
