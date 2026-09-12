param([string]$profilingType = "VTuneHotspots")

FileArb.exe create-binary-files `
   --target="X:\PerformanceTestingInputFiles\Cloudundancy\$profilingType" `
   --directories="10" `
   --files="100" `
   --bytes="4094" `
   --parallel `
   --quiet
