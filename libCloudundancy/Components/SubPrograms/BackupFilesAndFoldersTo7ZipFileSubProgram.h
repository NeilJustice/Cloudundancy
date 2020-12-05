#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
struct CloudundancyArgs;
class CloudundancyFileCopier;

class BackupFilesAndFoldersTo7ZipFileSubProgram : public CloudundancySubProgram
{
   friend class BackupFilesAndFoldersTo7ZipFileSubProgramTests;
private:
   // Function Callers
   using VoidOneArgFunctionCallerType = VoidOneArgMemberFunctionCaller<
      BackupFilesAndFoldersTo7ZipFileSubProgram, const CloudundancyArgs&>;
   unique_ptr<const VoidOneArgFunctionCallerType> _voidOneArgFunctionCaller;
   // Constant Components
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const ProcessRunner> _processRunner;
   unique_ptr<const Watch> _watch;
   // Mutable Components
   unique_ptr<Stopwatch> _stopwatch;
public:
   BackupFilesAndFoldersTo7ZipFileSubProgram();
   virtual ~BackupFilesAndFoldersTo7ZipFileSubProgram();
   virtual int Run(const CloudundancyArgs& args);
private:
   void Copy7ZipFileToDestinationFolders(const CloudundancyArgs& args) const;
   void CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const;
   void DeleteBackupStagingFolder(const CloudundancyArgs& args) const;
   void SevenZipBackupStagingFolder(const CloudundancyArgs& args) const;
};
