import collections
import functools
import os
import pathlib
import shutil

def current_directory_name():
   currentDirectoryPath = os.getcwd()
   splitCurrentDirectoryPath = currentDirectoryPath.split(os.sep)
   currentDirectoryName = splitCurrentDirectoryPath[len(splitCurrentDirectoryPath) - 1]
   return currentDirectoryName

def remove_folder_if_exists(folderPath):
   if os.path.exists(folderPath):
      shutil.rmtree(folderPath)

def copy_doth_and_dotcpp_files(sourceFolderPath, destFolderPath):
   sourceFilePaths = get_all_filepaths(sourceFolderPath)
   sourceAndHeaderFilePaths = filter(filepath_ends_with_doth_or_dotcpp, sourceFilePaths)
   copyHeaderFilesToDestFolder = functools.partial(copy_file, destFolderPath)
   collections.deque(map(copyHeaderFilesToDestFolder, sourceAndHeaderFilePaths), maxlen=0)
   print('Copied .h and .cpp files recursively from folder', sourceFolderPath, 'to folder', destFolderPath)

def get_all_filepaths(folderPath):
   filePaths = []
   for dirpath, _, filenames in os.walk(folderPath):
      for filename in filenames:
         filePath = os.path.join(dirpath, filename)
         filePaths.append(filePath)
   return filePaths

def get_folderpaths_in_folder(folderPath):
   folderPathPath = pathlib.Path(folderPath)
   windowsFolderPaths = []
   for path in folderPathPath.iterdir():
      if path.is_dir():
         windowsFolderPaths.append(path)
   return windowsFolderPaths

def filepath_ends_with_doth_or_dotcpp(filePath):
   filePathEndsWithDotHOrDotCpp = filePath.endswith('.h') or filePath.endswith('.cpp')
   return filePathEndsWithDotHOrDotCpp

def copy_file(destFolderPath, sourceFilePath):
   destFilePath = os.path.join(destFolderPath, sourceFilePath)
   destFilePathDirName = os.path.dirname(destFilePath)
   os.makedirs(destFilePathDirName, exist_ok=True)
   shutil.copy(sourceFilePath, destFilePath)

def install_copy_file(sourceFilePath, destFilePath):
   shutil.copyfile(sourceFilePath, destFilePath)
   print('Copied', sourceFilePath, 'to', destFilePath)
