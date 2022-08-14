
import os

filePrefixes = []
for file in list(os.listdir(os.path.curdir)):
    if ".py" in file:
        filePrefix = file.split(".py")[0]
        filePrefixes.append(filePrefix)
        
portablizerFile = "chelpers.py"


with open(portablizerFile, 'w+') as f:
    for prefix in filePrefixes:
        fileName = f'import {prefix}\n'
        f.write(fileName)

