import sys
import os
import shutil

buildDir = ''
if(len(sys.argv) > 2):
    buildDir = sys.argv[1]
else:
    buildDir = 'cmakebuild'

if(os.path.exists(os.getcwd() + buildDir)):
    shutil.rmtree(os.getcwd() + buildDir)

os.system('cmake -S . -B ' + buildDir)