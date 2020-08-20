# Imports
import sys
sys.path.append('../../PythonWrapper')
from ObjectCubePython import *

# Set the database location
hub = Hub.getHub()

#############################################################################################
tagset = AlphanumericalTagSet('TEXT').create()
textDimension = tagset.createPersistentDimension( tagset.fetchOrAddTag("TEXT") )
#############################################################################################

#############################################################################################
tagset = AlphanumericalTagSet('Location').create()
locationDimension = tagset.createPersistentDimension( tagset.fetchOrAddTag("Location") )
rootNode = locationDimension.getRoot()

cabinsNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Cabins"))
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Landmannalaugar") )
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Hrafntinnusker") )
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Emstrur") )
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Alftavatn") )
#############################################################################################

#############################################################################################
tagset = AlphanumericalTagSet('FileType').create()
fileTypeDimension = tagset.createPersistentDimension( tagset.fetchOrAddTag("FileType") )
rootNode = fileTypeDimension.getRoot()
fileTypeDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Image") )
fileTypeDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Text") )
#############################################################################################

#############################################################################################
tagset = AlphanumericalTagSet('Hike').create()
hikeDimension = tagset.createPersistentDimension( tagset.fetchOrAddTag("Hike") )
rootNode = hikeDimension.getRoot()
hikeDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Day 1") )
hikeDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Day 2") )
hikeDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Day 3") )
hikeDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Day 4") )
#############################################################################################

