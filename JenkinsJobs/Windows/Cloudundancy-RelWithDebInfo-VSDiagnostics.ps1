AcceliTune.exe build-then-collect-vsdiagnostics `
   --working-dir="."  `
   --solution=Cloudundancy `
   --program=Cloudundancy `
   --configuration=RelWithDebInfo `
   --args-file="JenkinsJobs\Windows\VSDiagnosticsArgs.txt" `
   --session-id=62 `
   --diagsession-output-file="D:\PerformanceProfilingResults\VSDiagnostics\Cloudundancy-RelWithDebInfo-VSDiagnostics.diagsession" `
   --prerun-powershell-script="Scripts\Windows\GenerateDataForSequentialProfiling.ps1"
