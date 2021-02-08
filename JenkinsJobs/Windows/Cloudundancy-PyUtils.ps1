Set-PSDebug -Trace 1

$env:PYTHONPATH = '.'
python.exe PyUtils\CoverageLintInstallPythonLibrary.py `
	--project=PyUtils `
	--test-project=PyUtilsTests `
	--run-tests-with-coverage-python-file=PyUtilsTests/RunAllWithCoverage.py

Set-PSDebug -Trace 0
