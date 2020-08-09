import os

def read_text(filePath):
   with open(filePath, 'r') as file:
      fileText = file.read()
      return fileText

def read_lines(filePath):
   with open(filePath, 'r') as file:
      fileLines = file.readlines()
      return fileLines

def write_text(filePath, text):
   with open(filePath, 'w') as file:
      file.write(text)

def write_lines(filePath, lines):
   dirName = os.path.dirname(filePath)
   os.makedirs(dirName, exist_ok=True)
   with open(filePath, 'w') as file:
      linesWithNewlineEndings = list(map(lambda line: line + '\n', lines))
      file.writelines(linesWithNewlineEndings)

def delete(filePath):
   if os.path.exists(filePath):
      os.remove(filePath)
