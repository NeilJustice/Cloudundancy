$env:PYTHONPATH="CloudundancyDevOpsPython"
python.exe -u CloudundancyDevOpsPython\CloudundancyDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-build-type=RelWithDebInfo `
   --tests-project-name=libCloudundancyTests `
   --cmake-definitions="-DCMAKE_INSTALL_PREFIX=C:\\" `
   --install
exit $LastExitCode
