import collections
import functools
import os
import platform
import sys
from PyUtils import File, Process

def generate(folderPath, generator, architecture, buildType, cmakeDefinitions, cmakeListsFolderPath):
   os.makedirs(folderPath, exist_ok=True)
   os.chdir(folderPath)
   print('Generating CMake in folder', folderPath)
   if platform.system() == 'Linux':
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" -DCMAKE_BUILD_TYPE={buildType} {cmakeDefinitions} {cmakeListsFolderPath}'
   else:
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" -A"{architecture}" {cmakeDefinitions} {cmakeListsFolderPath}'
   Process.fail_fast_run(cmakeCommand)

def generate_in_folder(folderPath, generator, architecture, buildType, cmakeListsFolderPath):
   os.makedirs(folderPath, exist_ok=True)
   os.chdir(folderPath)
   print('Generating CMake in folder', folderPath)
   if platform.system() == 'Linux':
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" -DCMAKE_BUILD_TYPE={buildType} {cmakeListsFolderPath}'
   else:
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" -A"{architecture}" {cmakeListsFolderPath}'
   Process.fail_fast_run(cmakeCommand)

def generate_all(baseFolderPath, folderNamesContainingCMakeLists):
   osPathJoinPartialBaseFolderPath = functools.partial(os.path.join, baseFolderPath)
   folderPathsContainingCMakeLists = list(map(
      osPathJoinPartialBaseFolderPath, folderNamesContainingCMakeLists))
   boundGenerateInFolder = functools.partial(
      generate_in_folder, generator='Visual Studio 16 2019', architecture='x64', buildType='N/A', cmakeListsFolderPath='.')
   collections.deque(map(boundGenerateInFolder, folderPathsContainingCMakeLists), maxlen=0)

def delete_cmake_cache_file_then_cmake():
   File.delete('CMakeCache.txt')
   generate('.', 'Visual Studio 16 2019', 'x64', '', '-DCMAKE_INSTALL_PREFIX=C:\\', '.')

def main(argv):
   if len(argv) == 2 and argv[1] == 'DeleteCacheThenCMake':
      delete_cmake_cache_file_then_cmake()

if __name__ == '__main__': # pragma nocover
   main(sys.argv)
