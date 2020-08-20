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
image_folder = '/home/snorri/Desktop/TextFile/'

for line in open('/home/snorri/Desktop/TextFile/PluginTextTags.csv'):
    ldata = line.split(',')[0].split(':')[:-1]
    #print ldata
    
    imageName = ldata[0].strip().replace('"','')
   

    img_path = os.path.join(image_folder, imageName)
    
    print 'processing text:', img_path
    
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

    
    '''
    # Create a thumbnail for the image that we are adding.
    tn = Image.open(img_path)
    tn.thumbnail((200, 200), Image.ANTIALIAS)
    tn_location = os.path.join(image_folder, 'T_' + imageName)
    tn.save(tn_location, "JPEG")
    #print 'Creating thumbnail %s' % tn_location
    #print 'object created', image_folder + '/' + imageName

    #print tn_location
    
    red = 0
    green = 0
    blue = 0
    count = 0
    with WandImage(filename=tn_location) as image:
        for row in image:
            for col in row:
                assert isinstance(col, Color)
                red += col.red_int8
                green += col.green_int8
                blue += col.blue_int8
                count += 1

    RGB = str(red / count) + ';'  + str(green / count) + ';' + str(blue / count)
    #print 'RGB: ' + RGB

    currentTagset = hub.getTagSet('RGB')
    tag = currentTagset.fetchOrAddTag(RGB)
    objectTag = ObjectTag(tag)
    objectCubeObject.addTag(objectTag)
    '''
    #objectCubeObject = Object.fetch(image_folder + '/' + imageName)

    for n in range(1,len(ldata)):
        if n % 2:
            #print n
            try:
                tagsetName = ldata[n]
                #print 'tagsetName' + tagsetName
                #print 'ldata[n+1]' + ldata[n+1] 
                currentTagset = hub.getTagSet(tagsetName)
                tag = currentTagset.fetchOrAddTag(ldata[n+1])
                objectTag = ObjectTag(tag)
                objectCubeObject.addTag(objectTag)
            except:
                pass
        #else:
        #    tag = currentTagset.fetchOrAddTag(ldata[n])
        #    objectTag = ObjectTag(tag)
        #    objectCubeObject.addTag(objectTag)
            #print '- added tag', tag, 'to image', imageName
