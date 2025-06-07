$env:PYTHONPATH="CloudundancyDevOpsPython"
python.exe -u CloudundancyDevOpsPython\CloudundancyDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=Cloudundancy `
   --cmake-build-type=Debug `
   --tests-project=libCloudundancyTests `
   --cmake-definitions="" `
   --no-install
exit $LastExitCode
