param([string]$profilingType = "VTuneHotspots")

FileArb.exe create-binary-files `
   --target="D:\PerformanceTestingInputFiles\Cloudundancy\$profilingType" `
   --directories="10" `
   --files="10" `
   --bytes="4094" `
   --parallel `
   --quiet
