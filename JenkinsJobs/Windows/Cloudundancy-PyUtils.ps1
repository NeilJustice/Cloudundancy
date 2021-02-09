Set-PSDebug -Trace 1

$env:PYTHONPATH = '.'
python.exe CloudundancyPyUtils\CoverageLintInstallPythonLibrary.py `
	--project=CloudundancyPyUtils `
	--run-tests-with-coverage-python-file=CloudundancyPyUtilsTests/RunAllWithCoverage.py

Set-PSDebug -Trace 0
exit $LastExitCode
