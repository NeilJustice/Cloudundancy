#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
struct CloudundancyArgs;
class CloudundancyFileCopier;

class BackupFilesAndFoldersTo7zFileSubProgram : public CloudundancySubProgram
{
   friend class BackupFilesAndFoldersTo7zFileSubProgramTests;
private:
   // Function Callers
   using VoidOneArgFunctionCallerType = VoidOneArgMemberFunctionCaller<
      BackupFilesAndFoldersTo7zFileSubProgram, const CloudundancyArgs&>;
   unique_ptr<const VoidOneArgFunctionCallerType> _voidOneArgFunctionCaller;
   // Constant Components
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const ProcessRunner> _processRunner;
   unique_ptr<const Watch> _watch;
   // Mutable Components
   unique_ptr<Stopwatch> _stopwatch;
public:
   BackupFilesAndFoldersTo7zFileSubProgram();
   virtual ~BackupFilesAndFoldersTo7zFileSubProgram();
   virtual int Run(const CloudundancyArgs& args);
private:
   void Copy7zFileToDestinationFolders(const CloudundancyArgs& args) const;
   void CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const;
   void DeleteBackupStagingFolder(const CloudundancyArgs& args) const;
   void SevenZipBackupStagingFolder(const CloudundancyArgs& args) const;
};
