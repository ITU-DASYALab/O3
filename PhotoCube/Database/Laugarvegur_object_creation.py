# Imports
import sys
sys.path.append('../../PythonWrapper')
from ObjectCubePython import Hub, Object, Parameters, ObjectTag
import os
import os.path
from PIL import Image

# Set the database location
#Parameters.getParameters().add( "SQLite", "laugarvegur.db" )
Parameters.getParameters().add("MonetDB_database", "objectcube")
hub = Hub.getHub()

currentTagset = None




def addObject(folder, filename):
    imgFullPath = os.path.join(folder, filename)
    # Create Object for this new image.
    try:
        Object(imgFullPath).create()
    except:
        pass

    try:
        print '-- added image ', imgFullPath

        # Create a thumbnail for the image that we are adding.
        tn_location = os.path.join(folder, 'T_' + filename)

        if os.path.exists(tn_location):
            print 'already exists! not creating thumbnail for', tn_location
            return

        tn = Image.open(imgFullPath)
        tn.thumbnail((200, 200), Image.ANTIALIAS)
        tn.save(tn_location, "JPEG")
        print '-- thumbnail created ', tn_location

    except Exception as inst:
        print 'error when create image', inst
        pass


def load():
    # READ IMAGES
    image_folder = '/l'
    with open('TagsPerImage.csv') as fs:
        for i, line in enumerate(fs):
            print 'Processing line', i
            ldata = line.split(',')[0].split(':')[:-1]
            #print ldata

            image_name = ldata[0].strip().replace('"','')
            image_full_path = os.path.join(image_folder, image_name)


            # Check if image exists
            if not os.path.exists(image_full_path):
                print 'image', image_full_path, 'does not exist!'
                continue

            #print 'processing', image_full_path

            try:
                addObject(image_folder, image_name)
            except:
                pass

            objectCubeObject = Object.fetch(image_full_path)
            print 'object created', image_full_path

            # Create thumbnail!

            for n in range(1,len(ldata)):
                if n % 2:
                    tagsetName = ldata[n]
                    currentTagset = hub.getTagSet(tagsetName)
                else:
                    tag = currentTagset.fetchOrAddTag(ldata[n])
                    objectTag = ObjectTag(tag)
                    objectCubeObject.addTag(objectTag)
                    print '- added tag', tag, 'to image', image_full_path

if __name__ == '__main__':
    load()