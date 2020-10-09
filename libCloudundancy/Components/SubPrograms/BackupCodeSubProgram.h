#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
class Console;
class CloudundancyFileCopier;
class FileSystem;
struct CloudundancyArgs;
class ProcessRunner;
class Stopwatch;
template<typename ClassType, typename ArgType>
class VoidOneArgMemberFunctionCaller;
class Watch;

class BackupCodeSubProgram : public CloudundancySubProgram
{
   friend class BackupCodeSubProgramTests;
private:
   // Constant Components
   unique_ptr<const Console> _console;
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const ProcessRunner> _processRunner;
   unique_ptr<const Watch> _watch;
   // Function Callers
   using VoidOneArgFunctionCallerType = VoidOneArgMemberFunctionCaller<BackupCodeSubProgram, const CloudundancyArgs&>;
   unique_ptr<const VoidOneArgFunctionCallerType> _voidOneArgFunctionCaller;
   // Mutable Components
   unique_ptr<Stopwatch> _stopwatch;
public:
   BackupCodeSubProgram();
   virtual ~BackupCodeSubProgram();
   virtual void Run(const CloudundancyArgs& args);
private:
   void Copy7zFileToDestinationFolders(const CloudundancyArgs& args) const;
   void CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const;
   void DeleteBackupStagingFolder(const CloudundancyArgs& args) const;
   void SevenZipBackupStagingFolder(const CloudundancyArgs& args) const;
};
