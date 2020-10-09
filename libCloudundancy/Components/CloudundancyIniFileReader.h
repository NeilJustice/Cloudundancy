#pragma once
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"

struct FilePathLineNumberLineText;
class FileSystem;

template<typename CollectionType, typename ClassType, typename FunctionType>
class MemberForEacher;

template<typename ReturnType, typename ClassType, typename ArgType>
class NonVoidOneArgMemberFunctionCaller;

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;

class CloudundancyIniFileReader
{
   friend class CloudundancyIniFileReaderTests;
private:
   // Constant Components
   unique_ptr<const FileSystem> _fileSystem;

   // Function Callers
   using NonVoidOneArgMemberFunctionCallerType =
      const NonVoidOneArgMemberFunctionCaller<AbsoluteFileOrFolderPathToRelativeFolderPath, CloudundancyIniFileReader, const FilePathLineNumberLineText&>;
   unique_ptr<NonVoidOneArgMemberFunctionCallerType> _caller_ParseFileCopyInstructionLine;

   using VoidTwoArgMemberFunctionCallerType =
      const VoidTwoArgMemberFunctionCaller<CloudundancyIniFileReader, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const FilePathLineNumberLineText&>;
   unique_ptr<VoidTwoArgMemberFunctionCallerType> _caller_ThrowIfSourceFileOrFolderDoesNotExist;
public:
   CloudundancyIniFileReader() noexcept;
   virtual ~CloudundancyIniFileReader();
   virtual CloudundancyIni ReadIniFile(const fs::path& cloudundancyIniPath) const;
private:
   AbsoluteFileOrFolderPathToRelativeFolderPath ParseFileCopyInstructionLine(
      const FilePathLineNumberLineText& fileCopyInstructionLine) const;
   void ThrowIfSourceFileOrFolderDoesNotExist(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
      const FilePathLineNumberLineText& filePathLineNumberLineText) const;
};
