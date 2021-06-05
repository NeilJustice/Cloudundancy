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
   -I C:\include\ZenUnitAndMetalMock `
   -I libCloudundancy `
   -I . `
   -j 48 `
   --output-file=cppcheck_results.txt `
   --error-exitcode=1 `
   .
if ($LastExitCode -eq 1)
{
   Get-Content cppcheck_results.txt
   Write-Host "Cppcheck failed with exit code 1"
   exit 1
}
