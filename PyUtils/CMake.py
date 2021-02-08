import os
import platform
import sys
from PyUtils import File, Process

def generate(folderPath, generator, buildType, cmakeDefinitions, cmakeListsFolderPath):
   os.makedirs(folderPath, exist_ok=True)
   os.chdir(folderPath)
   print('Generating CMake in folder', folderPath)
   if platform.system() == 'Linux':
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" -DCMAKE_BUILD_TYPE={buildType} {cmakeDefinitions} {cmakeListsFolderPath}'
   else:
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" {cmakeDefinitions} {cmakeListsFolderPath}'
   Process.fail_fast_run(cmakeCommand)

def delete_cmake_cache_file_then_cmake():
   File.delete('CMakeCache.txt')
   generate('.', 'Visual Studio 16 2019', '', '-DCMAKE_INSTALL_PREFIX=C:\\', '.')

def main(argv):
   if len(argv) == 2 and argv[1] == 'DeleteCacheThenCMake':
      delete_cmake_cache_file_then_cmake()

if __name__ == '__main__': # pragma nocover
   main(sys.argv)
