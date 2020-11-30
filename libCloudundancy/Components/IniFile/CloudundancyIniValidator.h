#pragma once
struct CloudundancyIni;
template<typename ClassType, typename ElementType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacher;

class CloudundancyIniValidator
{
private:
   using _memberForEach_ThrowIfFolderNotWritableType = OneExtraArgMemberFunctionForEacher<
      CloudundancyIniValidator, const fs::path&, const fs::path&>;
   //unique_ptr<const OneExtraArgMemberFunctionForEacher> _memberForEach_ThrowIfFolderNotWritable;
public:
   virtual ~CloudundancyIniValidator() = default;
   virtual void ThrowIfZeroDestinationFolderPaths(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
   virtual void ThrowIfAnyDestinationFoldersNotWritable(
      const CloudundancyIni& cloudundancyIni, const fs::path& cloudundancyIniPath) const;
private:
   void ThrowIfFolderNotWritable(const fs::path& folderPath, const fs::path& cloudundancyIniPath) const;
};
