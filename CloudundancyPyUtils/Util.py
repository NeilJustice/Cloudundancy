import os
import sys
import pprint

def home_folder_join(folderPath, fileName):
   homeFolderPath = os.path.expanduser('~')
   joinedHomeFolderPath = os.path.join(homeFolderPath, folderPath, fileName)
   return joinedHomeFolderPath

def code_folder_join(folderPath):
   homeFolderPath = os.path.expanduser('~')
   codeFolderPath = os.path.join(homeFolderPath, 'Code')
   joinedCodeFolderPath = os.path.join(codeFolderPath, folderPath)
   return joinedCodeFolderPath

def pretty_print(value):
   pprint.pprint(value)

def print_and_input(message):
   print(message)
   input()

def print_and_exit(message, exitCode):
   print(message)
   sys.exit(exitCode)
