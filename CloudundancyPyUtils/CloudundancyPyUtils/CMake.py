import os
import platform
from CloudundancyPyUtils import Process

def generate(folderPath, generator, buildType, cmakeDefinitions, cmakeListsFolderPath):
   os.makedirs(folderPath, exist_ok=True)
   os.chdir(folderPath)
   print('Generating CMake in folder', folderPath)
   if platform.system() == 'Linux':
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" -DCMAKE_BUILD_TYPE={buildType} {cmakeDefinitions} {cmakeListsFolderPath}'
   else:
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" {cmakeDefinitions} {cmakeListsFolderPath}'
   Process.fail_fast_run(cmakeCommand)
