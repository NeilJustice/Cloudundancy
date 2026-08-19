$args = "copy-files-to-multiple-folders " +
"--ini-file=C:\Code\Cloudundancy\TestingIniFiles\Windows\Cloudundancy_VTuneHotspots.ini " +
"--delete-destination-folders-first"

AcceliTune.exe build-then-collect-hotspots `
   --working-dir="." `
   --program="Cloudundancy" `
   --configuration=RelWithDebInfo `
   --args="$args" `
   --results-folder="D:\PerformanceProfilingResults\VTune\Cloudundancy_Hotspots" `
   --overwrite-results-folder
