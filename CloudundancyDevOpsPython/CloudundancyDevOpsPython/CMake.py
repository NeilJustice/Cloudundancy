import os
import platform
from CloudundancyDevOpsPython import Process

def generate(folderPath: str, generator: str, buildType: str, cmakeDefinitions: str, cmakeListsFolderPath: str) -> None:
   os.makedirs(folderPath, exist_ok=True)
   os.chdir(folderPath)
   print('Generating CMake in folder', folderPath)
   if platform.system() == 'Linux':
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" -DCMAKE_BUILD_TYPE={buildType} {cmakeDefinitions} {cmakeListsFolderPath}'
   else:
      cmakeCommand = f'cmake -Werror=dev -G"{generator}" {cmakeDefinitions} {cmakeListsFolderPath}'
   Process.fail_fast_run(cmakeCommand)
