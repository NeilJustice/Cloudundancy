#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
struct CloudundancyArgs;
class CloudundancyFileCopier;
class CloudundancyFileSystem;

class SevenZipSubProgram : public CloudundancySubProgram
{
   friend class SevenZipSubProgramTests;
private:
   // Function Callers
   using VoidOneArgFunctionCallerType = Utils::VoidOneArgMemberFunctionCaller<SevenZipSubProgram, const CloudundancyArgs&>;
   unique_ptr<const VoidOneArgFunctionCallerType> _voidOneArgFunctionCaller;
   // Constant Components
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
   unique_ptr<const CloudundancyFileSystem> _cloudundancyFileSystem;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Utils::ProcessRunner> _processRunner;
   unique_ptr<const Utils::Watch> _watch;
   // Mutable Components
   unique_ptr<Utils::Stopwatch> _stopwatch;
public:
   SevenZipSubProgram();
   virtual ~SevenZipSubProgram();
   int Run(const CloudundancyArgs& args) override;
private:
   void Copy7ZipFileToDestinationFolders(const CloudundancyArgs& args) const;
   void CopyFileToFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const;
   void DeleteBackupStagingFolder(const CloudundancyArgs& args) const;
   void SevenZipBackupStagingFolder(const CloudundancyArgs& args) const;
};
