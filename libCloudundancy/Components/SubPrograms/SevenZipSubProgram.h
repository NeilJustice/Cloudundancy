#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
namespace Utils
{
   template<typename ClassType>
   class VoidZeroArgMemberFunctionCaller;
}
class CloudundancyFileCopier;
class CloudundancyFileSystem;

class SevenZipSubProgram : public CloudundancySubProgram
{
   friend class SevenZipSubProgramTests;
private:
   // Function Callers
   using _voidZeroArgMemberFunctionCallerType = Utils::VoidZeroArgMemberFunctionCaller<SevenZipSubProgram>;
   unique_ptr<const _voidZeroArgMemberFunctionCallerType> _voidZeroArgMemberFunctionCaller;
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
   ~SevenZipSubProgram() override;
   int Run() override;
private:
   void Copy7ZipFileToDestinationFolders() const;
   void CopyFileToFilesAndFoldersToBackupStagingFolder() const;
   void DeleteBackupStagingFolder() const;
   void SevenZipBackupStagingFolder() const;
};
