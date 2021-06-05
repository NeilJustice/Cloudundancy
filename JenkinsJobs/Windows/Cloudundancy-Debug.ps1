param($fastWindowsDebugBuildMode = "ON")
Set-PSDebug -Trace 1

$env:PYTHONPATH="."
python.exe -u CloudundancyDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type=Debug `
   --tests-project=libCloudundancyTests `
   --cmake-definitions="-DFastWindowsDebugBuildMode=$fastWindowsDebugBuildMode" `
   --no-install

Set-PSDebug -Trace 0
exit $LastExitCode
