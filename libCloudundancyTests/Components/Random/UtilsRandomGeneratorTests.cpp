#include "pch.h"
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"

TESTS(UtilsRandomGeneratorTests)
AFACT(RelativeFilePath_ReturnsFilesystemPathWith0To2FoldersLeadingToARandomFilenameWithARandomFileExtension)
AFACT(RelativeFolderPath_ReturnsFilesystemPathWith0To2FoldersLeadingToARandomFolderName)
AFACT(RelativeFolderPaths_ReturnsVectorOfRandomFilesystemPathsBetweenSize0And2)
EVIDENCE

Utils::UtilsRandomGenerator _utilsRandomGenerator;

TEST(RelativeFilePath_ReturnsFilesystemPathWith0To2FoldersLeadingToARandomFilenameWithARandomFileExtension)
{
   fs::path relativeFilePath = _utilsRandomGenerator.RelativeFilePath();
   IS_NOT_EMPTY(relativeFilePath);
}

TEST(RelativeFolderPath_ReturnsFilesystemPathWith0To2FoldersLeadingToARandomFolderName)
{
   fs::path relativeFolderPath = _utilsRandomGenerator.RelativeFolderPath();
   IS_NOT_EMPTY(relativeFolderPath);
}

TEST(RelativeFolderPaths_ReturnsVectorOfRandomFilesystemPathsBetweenSize0And2)
{
   // 50 iterations for code coverage of the for-loop body in _utilsRandomGenerator.RelativeFolderPaths()
   for (size_t i = 0; i < 50; ++i)
   {
      vector<fs::path> relativeFolderPaths = _utilsRandomGenerator.RelativeFolderPaths();
      IS_TRUE(relativeFolderPaths.size() <= 2);
   }
}

RUN_TESTS(UtilsRandomGeneratorTests)
