#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RecursiveDirectoryIterator.h"
#include "libCloudundancyTests/UtilityComponents/Iteration/Transform/MetalMock/OneExtraArgTransformerMock.h"

TESTS(RecursiveDirectoryIteratorIntegrationTests)
AFACT(DefaultConstructor_NewsOneExtraArgTransformer_SetsFieldsToDefaultValues)
AFACT(IntegrationTest_RecursiveDirectoryIterator_EmptyFilePathIgnoreSubstrings_ReturnsAllFilePathsInAndBelowFolderPath)
AFACT(IntegrationTest_RecursiveDirectoryIterator_NonEmptyFilePathIgnoreSubstrings_ReturnsAllNonIgnoredFilePathsInAndBelowFolderPath)
EVIDENCE

Utils::RecursiveDirectoryIterator _recursiveDirectoryIterator;
Utils::FileSystem _fileSystem;
const fs::path _rootFolderPath = "IntegrationTest_RecursiveDirectoryIterator";

void CreateIntegrationTestingDirectoryStructure()
{
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "file1.txt", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "file2.ini", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "root.ignored_file_extension_1", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "root.ignored_file_extension_2", "");

   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir1" / "file1.xml", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir1" / "file2.json", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir1" / "file3.ignored_file_extension_1", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir1" / "file4.ignored_file_extension_2", "");

   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir2" / "file1.xml", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir2" / "file2.json", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir2" / "file3.ignored_file_extension_1", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir2" / "file4.ignored_file_extension_2", "");

   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "subdir3" / "subdir4" / "file1.html", "");

   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "ignored_directory_name_1" / "file1.txt", "");
   _fileSystem.CreateFileWithTextIfDoesNotExist(_rootFolderPath / "ignored_directory_name_2" / "file1.txt", "");
}

STARTUP
{
   CreateIntegrationTestingDirectoryStructure();
}

CLEANUP
{
   _fileSystem.DeleteFolder(_rootFolderPath);
}

TEST(DefaultConstructor_NewsOneExtraArgTransformer_SetsFieldsToDefaultValues)
{
   Utils::RecursiveDirectoryIterator recursiveDirectoryIterator;
   DELETE_TO_ASSERT_NEWED(recursiveDirectoryIterator._oneExtraArgTransformer);

   IS_DEFAULT_VALUE(recursiveDirectoryIterator._recursiveDirectoryIterator);
   ARE_EQUAL(vector<string>(), recursiveDirectoryIterator._fileSubpathsToIgnore);
}

TEST(IntegrationTest_RecursiveDirectoryIterator_EmptyFilePathIgnoreSubstrings_ReturnsAllFilePathsInAndBelowFolderPath)
{
   const vector<string> emptyFilePathIgnoreSubstrings;
   _recursiveDirectoryIterator.SetFileSubpathsToIgnore(emptyFilePathIgnoreSubstrings);
   _recursiveDirectoryIterator.InitializeIteratorAtFolderPath(_rootFolderPath);
   //
   const fs::path path1 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path2 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path3 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path4 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path5 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path6 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path7 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path8 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path9 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path10 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path11 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path12 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path13 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path14 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path15 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path16 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path17 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const vector<fs::path> actualFilePaths =
   {
      path1,
      path2,
      path3,
      path4,
      path5,
      path6,
      path7,
      path8,
      path9,
      path10,
      path11,
      path12,
      path13,
      path14,
      path15,
      path16,
      path17
   };
   //
   const vector<fs::path> expectedFilePaths =
   {
      _rootFolderPath / "file1.txt",
      _rootFolderPath / "file2.ini",
      _rootFolderPath / "root.ignored_file_extension_1",
      _rootFolderPath / "root.ignored_file_extension_2",

      _rootFolderPath / "subdir1" / "file1.xml",
      _rootFolderPath / "subdir1" / "file2.json",
      _rootFolderPath / "subdir1" / "file3.ignored_file_extension_1",
      _rootFolderPath / "subdir1" / "file4.ignored_file_extension_2",

      _rootFolderPath / "subdir2" / "file1.xml",
      _rootFolderPath / "subdir2" / "file2.json",
      _rootFolderPath / "subdir2" / "file3.ignored_file_extension_1",
      _rootFolderPath / "subdir2" / "file4.ignored_file_extension_2",

      _rootFolderPath / "subdir3" / "subdir4" / "file1.html",

      _rootFolderPath / "ignored_directory_name_1" / "file1.txt",
      _rootFolderPath / "ignored_directory_name_2" / "file1.txt",

      "",
      ""
   };
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedFilePaths, actualFilePaths);
}

TEST(IntegrationTest_RecursiveDirectoryIterator_NonEmptyFilePathIgnoreSubstrings_ReturnsAllNonIgnoredFilePathsInAndBelowFolderPath)
{
   const vector<string> filePathIgnoreSubstrings =
   {
      "ignored_file_extension",
      "ignored_directory_name"
   };
   _recursiveDirectoryIterator.SetFileSubpathsToIgnore(filePathIgnoreSubstrings);
   _recursiveDirectoryIterator.InitializeIteratorAtFolderPath(_rootFolderPath);
   //
   const fs::path path1 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path2 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path3 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path4 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path5 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path6 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path7 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path8 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const fs::path path9 = _recursiveDirectoryIterator.NextNonIgnoredFilePath();
   const vector<fs::path> actualFilePaths =
   {
      path1,
      path2,
      path3,
      path4,
      path5,
      path6,
      path7,
      path8,
      path9
   };
   //
   const vector<fs::path> expectedFilePaths =
   {
      _rootFolderPath / "file1.txt",
      _rootFolderPath / "file2.ini",

      _rootFolderPath / "subdir1" / "file1.xml",
      _rootFolderPath / "subdir1" / "file2.json",

      _rootFolderPath / "subdir2" / "file1.xml",
      _rootFolderPath / "subdir2" / "file2.json",

      _rootFolderPath / "subdir3" / "subdir4" / "file1.html",

      "",
      ""
   };
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedFilePaths, actualFilePaths);
}

RUN_TESTS(RecursiveDirectoryIteratorIntegrationTests)
