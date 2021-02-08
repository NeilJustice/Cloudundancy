Set-PSDebug -Trace 1

$env:PYTHONPATH = '.'
python.exe CloudundancyPyUtils\CoverageLintInstallPythonLibrary.py `
	--project=CloudundancyPyUtils `
	--run-tests-with-coverage-python-file=CloudundancyPyUtilsTests/RunAllWithCoverage.py
exit $LastExitCode

Set-PSDebug -Trace 0
