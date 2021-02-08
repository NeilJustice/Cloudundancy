Set-PSDebug -Trace 1

python.exe -u PyUtils\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type=Debug `
   --tests-project=libCloudundancyTests `
   --no-install
exit $LastExitCode

Set-PSDebug -Trace 0
