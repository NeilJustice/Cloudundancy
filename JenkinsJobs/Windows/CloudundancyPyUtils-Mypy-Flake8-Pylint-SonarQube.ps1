Set-PSDebug -Trace 1

cd CloudundancyPyUtils
$env:PYTHONPATH = '.'
python.exe CloudundancyPyUtils\MypyFlake8PylintRunTestsWithCoverage.py `
   --project=CloudundancyPyUtils `
   --run-tests-with-coverage-python-file=CloudundancyPyUtilsTests/RunAllWithCoverage.py
cd ..

Set-PSDebug -Trace 0
exit $LastExitCode
