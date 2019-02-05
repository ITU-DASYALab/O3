from ObjectCubePython import *
from ObjectCubePython import Hub, State
from PIL import Image
import sys
import os
import os.path

from wand.image import Image as WandImage
from wand.display import display
from wand.color import Color

#Parameters.getParameters().add( "MonetDB_database", "ObjectCube" )
hub = Hub.getHub()

# READ IMAGES
image_folder = '../LaugavegurPresentation/'

for line in open('../LaugavegurPresentation/LaugavegurImageTags.csv'):
    ldata = line.split(',')[0].split(':')[:-1]
    #print ldata
    
    imageName = ldata[0].strip().replace('"','')
   

    img_path = os.path.join(image_folder, imageName)
    
    print 'processing image:', img_path
    
    if not os.path.exists(img_path):
        print 'Skipping image %s, does not exist' % img_path
        continue
    
    objectCubeObject = Object(img_path)

    try:
        objectCubeObject.create()
    except:
        pass

    if not objectCubeObject:
        continue

    objectCubeObject = Object.fetch(img_path)

    
    
    # Create a thumbnail for the image that we are adding.
    tn = Image.open(img_path)
    tn.thumbnail((200, 200), Image.ANTIALIAS)
    tn_location = os.path.join(image_folder, 'T_' + imageName)
    tn.save(tn_location, "JPEG")

    for n in range(1,len(ldata)):
        if n % 2:
            try:
                tagsetName = ldata[n]
                currentTagset = hub.getTagSet(tagsetName)
                tag = currentTagset.fetchOrAddTag(ldata[n+1])
                objectTag = ObjectTag(tag)
                objectCubeObject.addTag(objectTag)
            except:
                pass

