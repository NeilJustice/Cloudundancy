Set-PSDebug -Trace 1

cd CloudundancyDevOpsPython
$env:PYTHONPATH = '.'
python.exe CloudundancyDevOpsPython\MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=CloudundancyDevOpsPythonTests/RunAllWithCoverage.py
cd ..

Set-PSDebug -Trace 0
exit $LastExitCode
