#pragma once

class CloudundancyFileSystem
{
   friend class CloudundancyFileSystemTests;
private:
   // Function Pointers
   using _fs_exists_FunctionOverloadType = bool(*)(const fs::path&);
   bool(*_call_fs_exists_as_assignable_function_overload_pointer)(const fs::path&);
   function<bool(const fs::path&)> _call_fs_exists;
   // Function Callers
   using _forEacher_DeleteContentsOfFolderExceptForFileNameType = Utils::OneExtraArgMemberFunctionForEacher<CloudundancyFileSystem, fs::path, string_view>;
   unique_ptr<const _forEacher_DeleteContentsOfFolderExceptForFileNameType> _forEacher_DeleteContentsOfFolderExceptForFileName;
   // Constant Components
   unique_ptr<const Utils::RawFileSystem> _rawFileSystem;
public:
   CloudundancyFileSystem();
   virtual ~CloudundancyFileSystem();
   virtual void DeleteMultipleFolderContentsExceptForFile(const vector<fs::path>& folderPaths, string_view exceptFileName) const;
   virtual void DeleteFolderContentsExceptForFile(const fs::path& folderPath, string_view exceptFileName) const;
   virtual bool IsFileSizeGreaterThanOrEqualTo2GB(const fs::path& filePath) const;
};
