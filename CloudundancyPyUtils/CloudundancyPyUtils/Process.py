import concurrent.futures
import multiprocessing
import os
import platform
import shlex
import subprocess
import sys
import threading
import time

def bytes_to_utf8(byteString):
   utf8 = byteString.decode('utf-8')
   return utf8

def run(command):
   shlexedCommand = shlex.split(command)
   completedProcess = subprocess.run(shlexedCommand, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
   completedProcess.stdout = bytes_to_utf8(completedProcess.stdout)
   completedProcess.stderr = bytes_to_utf8(completedProcess.stderr)
   return completedProcess

def fail_fast_run(command):
   exitCode = run_and_get_exit_code(command)
   if exitCode != 0:
      singleQuotedCommand = f'\'{command}\''
      print('Command', singleQuotedCommand, 'failed with exit code', exitCode)
      sys.exit(exitCode)

def cross_platform_subprocess_call(command):
   systemName = platform.system()
   if systemName.casefold() == 'windows':
      exitCode = subprocess.call(command)
   else:
      shlexedCommand = shlex.split(command)
      exitCode = subprocess.call(shlexedCommand)
   return exitCode

def run_and_get_exit_code(command):
   singleQuotedCommand = f'\'{command}\''
   currentWorkingDirectory = os.getcwd()
   print('Running', singleQuotedCommand, 'from', currentWorkingDirectory)
   try:
      exitCode = cross_platform_subprocess_call(command)
   except FileNotFoundError as ex:
      exceptionMessage = str(ex)
      print(exceptionMessage)
      sys.exit(1)
   else:
      return exitCode

def append_args(exePath, args):
   exePathWithArgs = exePath + (' ' + args if args != '' else '')
   return exePathWithArgs

def run_parallel_processpoolexecutor(func, iterable):
   cpuCount = multiprocessing.cpu_count()
   processPoolExecutor = concurrent.futures.ProcessPoolExecutor(cpuCount)
   exitCodes = processPoolExecutor.map(func, iterable)
   processPoolExecutor.shutdown(wait=True)
   allCommandsSucceeded = not any(exitCodes)
   return allCommandsSucceeded

class ProcessThread(threading.Thread): # pragma nocover

   def __init__(self, commandIndex, command, commandSuffixArg, outExitCodes):
      threading.Thread.__init__(self)
      self.commandIndex = commandIndex
      self.command = command
      self.commandSuffixArg = commandSuffixArg
      self.outExitCodes = outExitCodes

   def run(self):
      fullCommand = self.command + self.commandSuffixArg
      exitCode = run_and_get_exit_code(fullCommand)
      self.outExitCodes[self.commandIndex] = exitCode

def run_parallel_processthread(command, commandSuffixArgs): # pragma nocover
   numberOfCommands = len(commandSuffixArgs)
   processThreads = [None] * numberOfCommands
   processExitCodes = [None] * numberOfCommands
   beginTime = time.process_time()
   for commandIndex, commandSuffixArg in enumerate(commandSuffixArgs):
      processThread = ProcessThread(commandIndex, command, commandSuffixArg, processExitCodes)
      processThread.start()
      processThreads[commandIndex] = processThread
   for processThread in processThreads:
      processThread.join()
   endTime = time.process_time()
   elapsedMilliseconds = int((endTime - beginTime) * 1000)
   allProcessesExitedZero = not any(processExitCodes)
   print('Done in', elapsedMilliseconds, 'ms')
   print('All processes exited 0:', allProcessesExitedZero)
   return allProcessesExitedZero
