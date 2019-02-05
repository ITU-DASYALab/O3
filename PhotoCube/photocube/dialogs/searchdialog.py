# Python imports
import os
import os.path
import time

# Browser imports
from photocube.common.gui import createTextbox
from photocube.common.gui import createLabel
from photocube.common.gui import DirectOptionMenu
from photocube.common.gui import createImage

from abstract import AbstractDialog
from photocube.objectcube import objectCubeService
from photocube.objectcube import framework

from photocube.common import X_AXIS
from photocube.common import Y_AXIS
from photocube.common import Z_AXIS
from photocube.actions import ActionHierachy
from photocube.actions import actionManager

# Import action types.
from photocube.actions import ACTION_SET

from PIL import Image

class SearchDialog(AbstractDialog):
    """docstring for SearchDialog"""
    def __init__(self):
        # create np for the dialog.
        np = aspect2d.attachNewNode('AddTagFilterDialog')
        #super(ImportFilesDialog, self).__init__(self, np)
        AbstractDialog.__init__(self, np)
        
    
    
    def draw(self, tagset):
        #self.__create_components()
        self.create_ok_cancel_buttons()
        
        # Create all the components for this dialog.
        self.__initalizeComponents(tagset)
        
    def createThumbnail(self, folder, filename): # TODO same code as in addobject objectcube
        imgFullPath = os.path.join(folder, filename)
        # Create a thumbnail for the image that we are adding.
        tn = Image.open(imgFullPath)
        tn.thumbnail((200, 200), Image.ANTIALIAS)
        tn_location = os.path.join(folder, 'T_' + filename)
        tn.save(tn_location, "JPEG")
        return tn_location

    def showImage(self):
        print 'Virkadi'
        imageLocation = self.txtImage.get()
        if not os.path.isfile(imageLocation):
            print 'Warning: File doesnt exsist!'
            return

        value = os.path.split(imageLocation)
        self.url = self.createThumbnail(value[0], value[1])
        self.imageObject = createImage(parent=self.np, image = self.url, scale=(0.2), pos = (0, 0, -0.17))
        return self
    
    def __initalizeComponents(self, tagset):

        self.tagset = tagset

        width = 0.5

        items = []

        t_id = objectCubeService.get_tagset_by_id(self.tagset.id).typeId
        print 't_id' + str(t_id)
        if t_id == framework.TagSet.TYPE.ALPHANUMERICAL:
            print 'ALPHANUMERICAL'

            high = 0.25

            items.append('Search text')

            # Create label for text search.
            self.dialogTitleLabel = createLabel(parent=self.np, text='Search text', fg=(1,1,1,1), scale=(0.035), pos=(-0.30, high - 0.24))
            
            # Create textbox for text search.
            self.txtLocation = createTextbox(self.np, width=26, pos=(-0.40, 1, high - 0.29), scale=(0.03), focus=1)

        elif t_id == framework.TagSet.TYPE.RGB:
            print 'RGB'

            high = 0.55

            items.append('Search RGB')
            items.append('Search Image')

            base.accept('enter', self.showImage)

            # Create label for rgb search.
            self.dialogTitleLabel = createLabel(parent=self.np, text='Search RGB', fg=(1,1,1,1), scale=(0.035), pos=(-0.30, high - 0.24)) #high - 0.36

            self.dialogTitleLabel = createLabel(parent=self.np, text='Red', fg=(1,1,1,1), scale=(0.025), pos=(-0.375, high - 0.28)) #high - 0.40

            self.dialogTitleLabel = createLabel(parent=self.np, text='Green', fg=(1,1,1,1), scale=(0.025), pos=(-0.275, high - 0.28))

            self.dialogTitleLabel = createLabel(parent=self.np, text='Blue', fg=(1,1,1,1), scale=(0.025), pos=(-0.175, high - 0.28))

            self.dialogTitleLabel = createLabel(parent=self.np, text='Limit', fg=(1,1,1,1), scale=(0.025), pos=(0.35, high - 0.28))


            # Create textbox for rgb search.
            self.txtRed = createTextbox(self.np, width=2, pos=(-0.40, 1, high - 0.34), scale=(0.03), focus=1) #high - 0.46

            self.txtGreen = createTextbox(self.np, width=2, pos=(-0.30, 4, high - 0.34), scale=(0.03), focus=1)

            self.txtBlue = createTextbox(self.np, width=2, pos=(-0.20, 5, high - 0.34), scale=(0.03), focus=1)

            self.txtLimit = createTextbox(self.np, width=2, pos=(0.32, 5, high - 0.34), scale=(0.03), focus=1)

            # Create label for image search.
            self.dialogTitleLabel = createLabel(parent=self.np, text='Search image', fg=(1,1,1,1), scale=(0.035), pos=(-0.30, high - 0.43)) #high - 0.53
            
            # Create textbox for image search.
            self.txtImage = createTextbox(self.np, width=26, pos=(-0.40, 1, high - 0.48), scale=(0.03), focus=1) #high - 0.58

        

        

        # Set the window of the import window.
        self.bg.setScale(width, 1 , high)

        # Create label for text search.
        dimensionText = 'Tag-set: ' + tagset.name 
        self.dialogTitleLabel = createLabel(parent=self.np, text=dimensionText, fg=(1,1,1,1), scale=(0.045), pos=(-0.0, high - 0.1))

        # Drop box for search
        self.method_menu = DirectOptionMenu(text="options", 
                scale=0.045,
                text_scale=0.6,
                items=items,
                initialitem=0,
                highlightColor=(0.65,0.65,0.65,1),
                parent=self.np,
                rolloverSound=None,
                pos=(-0.40, 2, high - 0.17)
            )

        # Drop box for dimension
        self.dimension = DirectOptionMenu(text="options", 
                scale=0.045,
                text_scale=0.6,
                items=['front', 'in', 'up'],
                initialitem=0,
                highlightColor=(0.65,0.65,0.65,1),
                parent=self.np,
                rolloverSound=None,
                pos=(0.25, 2, high - 0.17)
            )

        # set the position of the ok/cancel buttons
        self.set_ok_button_pos((0.22, 1, 0.1 - high)) # 0.1 - high 
        self.set_cancel_button_pos((0.36, 1, 0.1 - high)) # 0.1 - high
    
    def search_text(self):
        text = self.txtLocation.get()
        if text == '':
            print 'Warning: Text box empty!'
            return
        values = str(self.tagset.id) + ';' + self.tagset.name + ';' + text + ';' + self.dimension.get()
        print values
        return objectCubeService.search_words(values)

    def search_rgb(self, limit):
        red = self.txtRed.get()
        green = self.txtGreen.get()
        blue = self.txtBlue.get()
        if red == '' or green == '' or blue == '':
            print 'Warning: RGB box empty!'
            return
        value = red + ";" + green + ";" + blue + ";" + limit + ";" + str(self.tagset.id) + ';' + self.dimension.get()
        print value
        return objectCubeService.search_rgb(value)

    def search_image(self, limit):
        return objectCubeService.search_image(self.url, limit, self.tagset.id, self.dimension.get())

    def constuct_cube(self, Ids):
        tagset = objectCubeService.get_tagset_by_id( int(Ids[0]) )
        # Get the hirarchy from the tagset.
        dim = tagset.getDimension( int( Ids[1] ))
        
        axis = ''
        if self.dimension.get() == 'front':
            axis = X_AXIS
        elif self.dimension.get() == 'up':
            axis = Z_AXIS
        elif self.dimension.get() == 'in':
            axis = Y_AXIS
        action = ActionHierachy(ACTION_SET, tagset.id, dim.id, axis)
        actionManager.addAction(action)
        messenger.send('dim_view_hierarchy', [axis, dim])
    
    def click_ok_button(self):
        print 'SEARCH OBJECT'
        
        
        Ids = ''
        if self.method_menu.get() == 'Search text':
            print 'Search text == True'
            Ids = self.search_text()
        elif self.method_menu.get() == 'Search RGB':
            print 'Search RGB == True'
            limit = self.txtLimit.get()
            if(limit == ""):
                limit = "-1";
            elif (not limit.isdigit()):
                print 'Provide number in limit'
                return
            print 'Limit: ' + limit
            Ids = self.search_rgb(limit)
        elif self.method_menu.get() == 'Search Image':
            print 'Search Image == True'
            limit = self.txtLimit.get()
            if(limit == ""):
                limit = "-1";
            elif (not limit.isdigit()):
                print 'Provide number in limit'
                return
            print 'Limit: ' + limit
            Ids = self.search_image(limit)

        if Ids != None:
            self.constuct_cube(Ids)
            # Close the dialog.
            self.np.remove()
            messenger.send('dialog_closing')
        
        return

    
