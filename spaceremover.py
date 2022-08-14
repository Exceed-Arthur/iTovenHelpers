import os

for file in list(os.listdir(os.path.curdir)):
    if ".py" in file:
        os.rename(file, file.replace(" ", ""))
            
