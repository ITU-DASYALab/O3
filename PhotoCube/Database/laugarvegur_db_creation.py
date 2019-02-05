# Imports
import sys
sys.path.append('../../PythonWrapper')
from ObjectCubePython import *

# Set the database location
#Parameters.getParameters().add( "MonetDB_database", "objectcube" )
Parameters.getParameters().add( "MonetDB_database", "objectcube" )
hub = Hub.getHub()


#############################################################################################
tagset = AlphanumericalTagSet('Gangan').create()
hikeDimension = tagset.createPersistentDimension( tagset.fetchOrAddTag("Gangan") )
hikeNode = hikeDimension.getRoot()
node = hikeDimension.addNode( hikeNode.id, tagset.fetchOrAddTag("Dagur 1") )
node = hikeDimension.addNode( hikeNode.id, tagset.fetchOrAddTag("Dagur 2") )
node = hikeDimension.addNode( hikeNode.id, tagset.fetchOrAddTag("Dagur 3") )
node = hikeDimension.addNode( hikeNode.id, tagset.fetchOrAddTag("Dagur 4") )
node = hikeDimension.addNode( hikeNode.id, tagset.fetchOrAddTag("Dagur 5") )
#############################################################################################

#############################################################################################
tagset = AlphanumericalTagSet('Stadir').create()
locationDimension = tagset.createPersistentDimension( tagset.fetchOrAddTag("Stadir") )
rootNode = locationDimension.getRoot()

cabinsNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Cabins"))
#locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Landmannalaugar") )
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Hrafntinnusker") )
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Hvanngil") )
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Emstrur") )
locationDimension.addNode( cabinsNode.id, tagset.fetchOrAddTag("Thorsmork") )

glacierNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Joklar"))
locationDimension.addNode( glacierNode.id, tagset.fetchOrAddTag("Eyjafjallajokull") )
locationDimension.addNode( glacierNode.id, tagset.fetchOrAddTag("Steinsholtsjokull") )
locationDimension.addNode( glacierNode.id, tagset.fetchOrAddTag("Myrdalsjokull") )

caveNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Hellar"))
locationDimension.addNode( caveNode.id, tagset.fetchOrAddTag("Songhellir") )
locationDimension.addNode( caveNode.id, tagset.fetchOrAddTag("Snorrariki") )

oasisNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Vinjar"))
locationDimension.addNode( oasisNode.id, tagset.fetchOrAddTag("Landmannalaugar") )
#locationDimension.addNode( oasisNode.id, tagset.fetchOrAddTag("Thorsmork") )
locationDimension.addNode( oasisNode.id, tagset.fetchOrAddTag("Langidalur") )

montainNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Fjoll"))
#locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Hrafntinnusker") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Sodull") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Einhyrningur") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Katla") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Utigonguhofdar") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Storkonufell") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Blahnukur") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Haskerdingur") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Svartihryggur") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Valahnukur") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Utigonguhofdi") )
locationDimension.addNode( montainNode.id, tagset.fetchOrAddTag("Hattafell") )

riverNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Ar"))
locationDimension.addNode( riverNode.id, tagset.fetchOrAddTag("Markarfljot") )
locationDimension.addNode( riverNode.id, tagset.fetchOrAddTag("Krossa") )
locationDimension.addNode( riverNode.id, tagset.fetchOrAddTag("Fremri Emstrua") )
locationDimension.addNode( riverNode.id, tagset.fetchOrAddTag("Blafjallakvisl") )
locationDimension.addNode( riverNode.id, tagset.fetchOrAddTag("Thronga") )

hotspringsNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Hverir"))
locationDimension.addNode( hotspringsNode.id, tagset.fetchOrAddTag("Brennisteinsalda"))
locationDimension.addNode( hotspringsNode.id, tagset.fetchOrAddTag("Storihver"))

lakeNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Votn"))
locationDimension.addNode( lakeNode.id, tagset.fetchOrAddTag("Alftavatn") )

canyonNode = locationDimension.addNode( rootNode.id, tagset.fetchOrAddTag("Gljufur"))
locationDimension.addNode( canyonNode.id, tagset.fetchOrAddTag("Markarfljotsgljufur") )
locationDimension.addNode( canyonNode.id, tagset.fetchOrAddTag("Slyppugil") )
locationDimension.addNode( canyonNode.id, tagset.fetchOrAddTag("Bjorgil") )
#############################################################################################



#############################################################################################
tagset = AlphanumericalTagSet('Jardfraedi').create()
# Create Geology hir
geologyDim = tagset.createPersistentDimension( tagset.fetchOrAddTag("Jardfraedi") )
rootNode = geologyDim.getRoot()
geologyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Hrafntinna"))
geologyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Liparit"))
geologyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Hraun"))
geologyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Aska"))
#############################################################################################



#############################################################################################
tagset = AlphanumericalTagSet('Hlutir').create()
objectDim = tagset.createPersistentDimension( tagset.fetchOrAddTag("Hlutir") )
rootNode = objectDim.getRoot()

equipmentNode = objectDim.addNode( rootNode.id, tagset.fetchOrAddTag("Utbunadur"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("Bakpoki"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("Gonguskor"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("Attavitit"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("GPS"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("Myndavel"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("Tjald"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("Ubudir"))
objectDim.addNode( equipmentNode.id, tagset.fetchOrAddTag("skilti"))

entertainmentNode = objectDim.addNode( rootNode.id, tagset.fetchOrAddTag("Skemmtun"))
objectDim.addNode( entertainmentNode.id, tagset.fetchOrAddTag("Risaedla"))
objectDim.addNode( entertainmentNode.id, tagset.fetchOrAddTag("Bolti"))
objectDim.addNode( entertainmentNode.id, tagset.fetchOrAddTag("Frisbi"))
objectDim.addNode( entertainmentNode.id, tagset.fetchOrAddTag("Nammi"))
objectDim.addNode( entertainmentNode.id, tagset.fetchOrAddTag("Matur"))
objectDim.addNode( entertainmentNode.id, tagset.fetchOrAddTag("Blom"))

vehiclesNode = objectDim.addNode( rootNode.id, tagset.fetchOrAddTag("Farartaeki"))
objectDim.addNode( vehiclesNode.id, tagset.fetchOrAddTag("Bill"))
objectDim.addNode( vehiclesNode.id, tagset.fetchOrAddTag("Flugvel"))
objectDim.addNode( vehiclesNode.id, tagset.fetchOrAddTag("Ruta"))
objectDim.addNode( vehiclesNode.id, tagset.fetchOrAddTag("Trussbill"))
#############################################################################################


#############################################################################################
tagset = AlphanumericalTagSet('Vidburdir').create()
eventsDim = tagset.createPersistentDimension( tagset.fetchOrAddTag("Vidburdir") )
rootNode = eventsDim.getRoot()

dayOneNode = eventsDim.addNode( rootNode.id, tagset.fetchOrAddTag("Dagur 1"))
eventsDim.addNode( dayOneNode.id, tagset.fetchOrAddTag("Bad i Landmannalaugum"))
eventsDim.addNode( dayOneNode.id, tagset.fetchOrAddTag("Fyrsta upphitun"))
eventsDim.addNode( dayOneNode.id, tagset.fetchOrAddTag("Raudur andlitsleir"))
eventsDim.addNode( dayOneNode.id, tagset.fetchOrAddTag("Rigningarpasa"))
eventsDim.addNode( dayOneNode.id, tagset.fetchOrAddTag("Vidgerd a stig"))
eventsDim.addNode( dayOneNode.id, tagset.fetchOrAddTag("Frisbi"))

dayTwoNode = eventsDim.addNode( rootNode.id, tagset.fetchOrAddTag("Dagur 2"))
eventsDim.addNode( dayTwoNode.id, tagset.fetchOrAddTag("Hvitur andlitsleir"))
eventsDim.addNode( dayTwoNode.id, tagset.fetchOrAddTag("Ishellir"))
eventsDim.addNode( dayTwoNode.id, tagset.fetchOrAddTag("Alftavatn"))
eventsDim.addNode( dayTwoNode.id, tagset.fetchOrAddTag("Vadid yfir Geithalskvisl"))
eventsDim.addNode( dayTwoNode.id, tagset.fetchOrAddTag("Vadid yfir Bratthalskvisl"))

dayThreeNode = eventsDim.addNode( rootNode.id, tagset.fetchOrAddTag("Dagur 3"))
eventsDim.addNode( dayThreeNode.id, tagset.fetchOrAddTag("Dressmann keppnin"))
eventsDim.addNode( dayThreeNode.id, tagset.fetchOrAddTag("Skotbolti"))
eventsDim.addNode( dayThreeNode.id, tagset.fetchOrAddTag("Pasa"))
eventsDim.addNode( dayThreeNode.id, tagset.fetchOrAddTag("Leikur i oskunni"))

dayFourNode = eventsDim.addNode( rootNode.id, tagset.fetchOrAddTag("Dagur 4"))
eventsDim.addNode( dayFourNode.id, tagset.fetchOrAddTag("Farid yfir bruna"))
eventsDim.addNode( dayFourNode.id, tagset.fetchOrAddTag("Vadid yfir Thronga"))
eventsDim.addNode( dayFourNode.id, tagset.fetchOrAddTag("Pasa i oskunni"))


dayFiveNode = eventsDim.addNode( rootNode.id, tagset.fetchOrAddTag("Dagur 5"))
eventsDim.addNode( dayFiveNode.id, tagset.fetchOrAddTag("Blomakeppnin"))
eventsDim.addNode( dayFiveNode.id, tagset.fetchOrAddTag("Fotbolti"))
eventsDim.addNode( dayFiveNode.id, tagset.fetchOrAddTag("Klifrad i Snorrariki"))
eventsDim.addNode( dayFiveNode.id, tagset.fetchOrAddTag("Vadid i fludunum"))
#############################################################################################


#############################################################################################
tagset = AlphanumericalTagSet('Folk').create()
peopleDim = tagset.createPersistentDimension( tagset.fetchOrAddTag("Folk") )
rootNode = peopleDim.getRoot()

adultsNode = peopleDim.addNode( rootNode.id, tagset.fetchOrAddTag("Fullordnir"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Magnus eldri"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Margret eldri"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Duddi"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Frida"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Kristinn"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Hrefna"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Asa"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Bjorn"))
peopleDim.addNode( adultsNode.id, tagset.fetchOrAddTag("Dori Truss"))

kidsNode = peopleDim.addNode( rootNode.id, tagset.fetchOrAddTag("Kids"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Magnus yngri"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Margret yngri"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Magnus Dudda"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Katrin"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Jokull"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Johannes"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Solveig"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Asthor"))
peopleDim.addNode( kidsNode.id, tagset.fetchOrAddTag("Kria"))

familyDim = tagset.createPersistentDimension( tagset.fetchOrAddTag("Family") )
rootNode = familyDim.getRoot()
familyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Asa"))
familyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Bjorn"))
familyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Solveig"))
familyDim.addNode( rootNode.id, tagset.fetchOrAddTag("Asthor"))
#############################################################################################+

#############################################################################################
tagset = AlphanumericalTagSet('Dyr').create()
animaleDimension = tagset.createPersistentDimension( tagset.fetchOrAddTag("Dyr") )
animalsNode = animaleDimension.getRoot()
node = animaleDimension.addNode( animalsNode.id, tagset.fetchOrAddTag("Kind") )
node = animaleDimension.addNode( animalsNode.id, tagset.fetchOrAddTag("Fugl") )
node = animaleDimension.addNode( animalsNode.id, tagset.fetchOrAddTag("Hundur") )
node = animaleDimension.addNode( animalsNode.id, tagset.fetchOrAddTag("Fiskur") )
#############################################################################################


#############################################################################################
tagset = AlphanumericalTagSet('Fegurd').create()
impressionHir = tagset.createPersistentDimension( tagset.fetchOrAddTag("Fegurd") )
imperssionNode = impressionHir.getRoot()
node = impressionHir.addNode( imperssionNode.id, tagset.fetchOrAddTag("Fallegar myndir") )
#############################################################################################
