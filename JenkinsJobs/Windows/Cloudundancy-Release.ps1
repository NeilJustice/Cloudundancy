param([string]$cmakeInstallPrefix = "C:\")

Set-PSDebug -Trace 1

python.exe -u PyUtils\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type=Release `
   --tests-project-name=libCloudundancyTests `
   --cmake-definitions="-DCMAKE_INSTALL_PREFIX=$cmakeInstallPrefix" `
   --install

Set-PSDebug -Trace 0
