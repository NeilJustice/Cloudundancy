$performanceTestingInputFilesFolderPath = "X:\PerformanceTestingInputFiles\Cloudundancy\PerformanceTest"

FileRevisor.exe delete-directory `
   --target="$performanceTestingInputFilesFolderPath" `
   --parallel `
   --quiet
if ($LastExitCode -ne 0) { exit $LastExitCode }
Write-Host

FileArb.exe create-binary-files `
   --target="$performanceTestingInputFilesFolderPath" `
   --directories="32" `
   --files="100" `
   --bytes="1M" `
   --parallel `
   --quiet
