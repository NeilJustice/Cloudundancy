$args = "copy-files-to-multiple-folders " +
"--ini-file=C:\Code\Cloudundancy\TestingIniFiles\Windows\Cloudundancy_PerformanceTest.ini " +
"--delete-destination-folders-first"

AcceliTune.exe build-then-measure-program-run-time `
   --working-dir="." `
   --program="Cloudundancy" `
   --configuration="RelWithDebInfo" `
   --args="$args" `
   --performance-test-results-file="C:\Code\WindowsPerformanceTestResults\Performance\Cloudundancy-Performance.txt"
