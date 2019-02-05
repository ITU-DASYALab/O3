# Python imports
import os
import os.path

# Browser imports
from photocube.common.gui import createTextbox
from photocube.common.gui import createLabel
from abstract import AbstractDialog
from photocube.objectcube import objectCubeService



class ImportFilesDialog(AbstractDialog):
    """docstring for ImportFilesDialog"""
    def __init__(self):
        # create np for the dialog.
        np = aspect2d.attachNewNode('AddTagFilterDialog')
        #super(ImportFilesDialog, self).__init__(self, np)
        AbstractDialog.__init__(self, np)
        
    
    
    def draw(self):
        #self.__create_components()
        self.create_ok_cancel_buttons()

        # set the position of the ok/cancel buttons
        self.set_ok_button_pos((0.22, 1,-0.16))
        self.set_cancel_button_pos((0.36, 1, -0.16))
        
        # Create all the components for this dialog.
        self.__initalizeComponents()
        
        
    
    def __initalizeComponents(self):
        # Set the window of the import window.
        self.bg.setScale(0.50, 1 ,0.25)
        
        # Create label for dialog title.
        self.dialogTitleLabel = createLabel(parent=self.np, text='Import image from folder', fg=(1,1,1,1), scale=(0.035), pos=(-0.22, 0.12))
        
        # Create textbox for folder location.
        self.txtLocation = createTextbox(self.np, width=26, pos=(-0.40, 1, 0.05), scale=(0.03), focus=1)
    
    
    
    def click_ok_button(self):
        print 'ADDING OBJECT'
        # Get the text that the users placed to the input textbox
        value = self.txtLocation.get()
        
        # Go through all the subdirectories and search for jpgs
        for root, dirs, files in os.walk(value):
            for f in files:
                fullpath = os.path.join(root, f)
                if fullpath.lower().endswith('.jpg'):
                    print 'adding', f
                    # add the object to current database.
                    objectCubeService.addObject(root, f)
                    
        
        # Close the dialog.
        self.np.remove()
        messenger.send('dialog_closing')
        return

    
