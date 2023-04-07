if [ $# -ge 1 ] 
then buildDir=$1
else buildDir="./cmakebuild"
fi

if [ -d "$buildDir" ]
then rm -r $buildDir
fi
	
cmake -B ./cmakebuild
exit 1