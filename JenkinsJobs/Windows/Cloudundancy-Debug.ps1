param($fastWindowsDebugBuildMode = "ON")
$env:PYTHONPATH="."
python.exe -u CloudundancyDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type=Debug `
   --tests-project=libCloudundancyTests `
   --cmake-definitions="-DFastWindowsDebugBuildMode=$fastWindowsDebugBuildMode" `
   --no-install
exit $LastExitCode
