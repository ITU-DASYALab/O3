import sys
sys.path.append( '../../ObjectCube' )

import ObjectCubePython

imageFolder = '/Users/hlynsig/temp/PhotoCubeImages/Laugavegur/'
textFile = '/Users/hlynsig/temp/PhotoCubeImages/Laugavegur/icmlaugarvegur.csv'


for line in open(textFile):
    print line
    