Set-PSDebug -Trace 1

$env:PYTHONPATH="CloudundancyPyUtils"
python.exe -u CloudundancyPyUtils\CloudundancyPyUtils\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type=Debug `
   --tests-project=libCloudundancyTests `
   --no-install

Set-PSDebug -Trace 0
exit $LastExitCode
