#pragma once
class CloudundancyIniValidator;

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

   using VoidOneArgMemberFunctionCallerType = const VoidOneArgMemberFunctionCaller<
      CloudundancyIniFileReader, const CloudundancyIniCopyInstruction&>;
   unique_ptr<VoidOneArgMemberFunctionCallerType> _caller_ThrowIfSourceFileOrFolderDoesNotExist;

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
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction) const;
};
