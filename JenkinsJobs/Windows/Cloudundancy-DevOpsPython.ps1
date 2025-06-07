cd CloudundancyDevOpsPython
$env:PYTHONPATH="."
python.exe -u "CloudundancyDevOpsPython\MypyFlake8PylintThenRunTestsWithCoverage.py" --run-tests-with-coverage-python-file="CloudundancyDevOpsPythonTests/RunAllWithCoverage.py"
exit $LastExitCode
