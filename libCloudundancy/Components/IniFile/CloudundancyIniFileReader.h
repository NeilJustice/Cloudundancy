#pragma once

template<typename ReturnType, typename ClassType, typename ArgType>
class NonVoidOneArgMemberFunctionCaller;

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;

class CloudundancyIniValidator;
class FileSystem;
struct FilePathLineNumberLineText;

class CloudundancyIniFileReader
{
   friend class CloudundancyIniFileReaderTests;
private:
   // Function Callers
   using NonVoidOneArgMemberFunctionCallerType = const NonVoidOneArgMemberFunctionCaller<
      CloudundancyIniCopyInstruction,
      CloudundancyIniFileReader,
      const FilePathLineNumberLineText&>;
   unique_ptr<NonVoidOneArgMemberFunctionCallerType> _caller_ParseFileCopyInstructionLine;

   using VoidTwoArgMemberFunctionCallerType = const VoidTwoArgMemberFunctionCaller<
      CloudundancyIniFileReader,
      const CloudundancyIniCopyInstruction&,
      const FilePathLineNumberLineText&>;
   unique_ptr<VoidTwoArgMemberFunctionCallerType> _caller_ThrowIfSourceFileOrFolderDoesNotExist;

   // Constant Components
   unique_ptr<const CloudundancyIniValidator> _cloudundancyIniValidator;
   unique_ptr<const FileSystem> _fileSystem;
public:
   CloudundancyIniFileReader() noexcept;
   virtual ~CloudundancyIniFileReader();
   virtual CloudundancyIni ReadIniFile(const fs::path& cloudundancyIniPath) const;
private:
   CloudundancyIniCopyInstruction ParseFileCopyInstructionLine(
      const FilePathLineNumberLineText& fileCopyInstructionLine) const;
   void ThrowIfSourceFileOrFolderDoesNotExist(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
      const FilePathLineNumberLineText& filePathLineNumberLineText) const;
};
