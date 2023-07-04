$env:PYTHONPATH="."
python.exe -u CloudundancyDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type=Release `
   --tests-project-name=libCloudundancyTests `
   --cmake-definitions="" `
   --no-install
exit $LastExitCode
