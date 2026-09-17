#pragma once
namespace Utils
{
   template<typename ClassType, typename T>
   class OneArgMemberFunctionForEacher;
}
class PassthroughFileSystem;

class CloudundancyFileSystem
{
   friend class CloudundancyFileSystemTests;
private:
   // Function Pointers
   using fs_exists_FunctionOverloadType = bool(*)(const fs::path&);
   bool(*_call_fs_exists_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_exists;
   // Function Callers
   using _forEacher_DeleteFolderType = Utils::OneArgMemberFunctionForEacher<CloudundancyFileSystem, fs::path>;
   unique_ptr<const _forEacher_DeleteFolderType> _forEacher_DeleteFolder;
   // Constant Components
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const PassthroughFileSystem> _passthroughFileSystem;
public:
   CloudundancyFileSystem();
   virtual ~CloudundancyFileSystem();

   virtual void DeleteFolder(const fs::path& folderPath) const;

   virtual void DeleteMultipleFolders(const vector<fs::path>& folderPaths) const;

   virtual bool FileSizeIsGreaterThanOrEqualTo2GB(const fs::path& filePath) const;
};
