$env:PYTHONPATH="."
python.exe -u CloudundancyDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type=RelWithDebInfo `
   --tests-project-name=libCloudundancyTests `
   --cmake-definitions="-DCMAKE_INSTALL_PREFIX=C:\" `
   --install
exit $LastExitCode
