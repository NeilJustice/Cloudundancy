Set-PSDebug -Trace 1

$env:PYTHONPATH = '.'
python.exe PyUtils\CoverageLintInstallPythonLibrary.py --project=PyUtils --run-tests-with-coverage-python-file=PyUtilsTests/RunAllWithCoverage.py
exit $LastExitCode

Set-PSDebug -Trace 0
