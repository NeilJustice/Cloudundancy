param([string]$profilingType = "VTuneHotspots")

$performanceTestingInputFilesFolderPath = "X:\PerformanceTestingInputFiles\Cloudundancy\$profilingType"

FileRevisor.exe delete-directory `
   --target="$performanceTestingInputFilesFolderPath" `
   --parallel `
   --quiet
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

FileArb.exe create-binary-files `
   --target="$performanceTestingInputFilesFolderPath" `
   --directories="32" `
   --files="300" `
   --bytes="4094" `
   --parallel `
   --quiet
