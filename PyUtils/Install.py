import os
from PyUtils import FileSystem, Util

def binary(projectName, configuration):
   solutionDirectory = os.getcwd()
   sourceBinaryPath = os.path.join(solutionDirectory, projectName, configuration, projectName + '.exe')
   destBinaryPath = Util.home_folder_join('bin', projectName + 'Installed.exe')
   FileSystem.install_copy_file(sourceBinaryPath, destBinaryPath)
