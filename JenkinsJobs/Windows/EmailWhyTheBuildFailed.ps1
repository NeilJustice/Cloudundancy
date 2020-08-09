EmailWhyTheBuildFailed.exe `
   --jenkins-computer-name=$ENV:ComputerName `
   --jenkins-url=$ENV:JENKINS_URL `
   --build-pipeline-name="" `
   --jenkins-job-path=$ENV:JOB_NAME `
   --build-configuration="" `
   --jenkins-build-number=$ENV:BUILD_NUMBER `
   --jenkins-job-workspace-folder=$ENV:WORKSPACE `
   --from-address="Jenkins@Emerson.com" `
   --to-addresses="Neil.Justice@Emerson.com"
