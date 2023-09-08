$numberOfLogicalProcessorsDividedBy2 = (Get-CimInstance -ClassName Win32_ComputerSystem).NumberOfLogicalProcessors / 2
cppcheck.exe `
   --enable=all `
   --cppcheck-build-dir=Cppcheck `
   --suppressions-list=CppcheckSuppressions.txt `
   -D_WIN32 `
   -DTEST `
   -DTESTS `
   -DMETALMOCK_VOID1_FREE `
   -DMETALMOCK_NONVOID0_FREE `
   -DMETALMOCK_NONVOID0_STATIC `
   -DMETALMOCK_NONVOID1_FREE `
   -DMETALMOCK_NONVOID1_STATIC `
   -DMETALMOCK_NONVOID2_STATIC `
   -DMETALMOCK_NONVOID5_FREE `
   -DTHEN_RUN_TEMPLATE_TESTS `
   -DRUN_TEMPLATE_TESTS `
   -DAFACT `
   -DFACTS `
   -DMETALMOCK_VOID2_CONST `
   -DMETALMOCK_NONVOID1_CONST `
   -DMETALMOCK_NONVOID0_CONST `
   -DMETALMOCK_NONVOID4_FREE `
   -DMETALMOCK_VOID1 `
   -DMETALMOCK_VOID1_CONST `
   -DMETALMOCK_NONVOID2_CONST `
   -DMETALMOCK_NONVOID2_FREE `
   -DMETALMOCK_NONVOID0 `
   -I . `
   -I C:\include\ZenUnitAndMetalMock `
   -I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um" `
   -I libCloudundancy `
   -j $numberOfLogicalProcessorsDividedBy2 `
   --output-file=cppcheck_results.txt `
   --error-exitcode=1 `
   .
if ($LastExitCode -eq 1)
{
   Get-Content cppcheck_results.txt
   Write-Host "Cppcheck failed with exit code 1"
   exit 1
}
