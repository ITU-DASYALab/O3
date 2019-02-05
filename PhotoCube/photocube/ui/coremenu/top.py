DEBUG = True

import sys

from pandac.PandaModules import NodePath, TextNode
from pandac.PandaModules import TransparencyAttrib
from direct.gui.DirectGui import *

import photocube.ui.coremenu
import photocube.dialogs
from photocube.ui.sounds import button_mouseclick_sound
from photocube.ui.fonts import font
from photocube.dialogs import dialogService


class MainButtonContainer:
    """
    This is the main menu that appears on the top of the page in the window.
    """
    def __init__(self):
        self.dbuttons = []
        self.load_buttons()
        base.taskMgr.add(self.placement, 'menuplacement_left_panel')
   
        

    def placement(self, task):
        x = 0.12
        for b in self.dbuttons:
            b.setX(-base.getAspectRatio() + x)
            b.setZ(0.95)
            x += 0.30
        return task.cont

    def load_buttons(self):
        buttons = []
        
        # add the button to the buttons list.
        buttons.append(('Quit', self.eventPressQuit))
        buttons.append(('settings', self.eventPressSettings))
        buttons.append(('new tagset', self.eventPressNewTagset))
        buttons.append(('import', self.eventPressImportImages))
        buttons.append(('add tagfilter', self.eventPressAddTagfiler))
        
        loc = 0
        self.dbuttons = []

        for b in buttons:

            b = DirectButton(
            text_fg=(1, 1, 1, 0.8), 
            frameColor=(0.3, 0.3, 0.3, 0.8), 
            relief=DGG.RAISED, 
            text=(b[0],b[0],b[0],""), 
            pressEffect=1, 
            scale=.040,
            frameSize=(-2.0, 2.0, -2, 2),
            text_scale = (1.1), 
            command=b[1], 
            rolloverSound=None,
            #text_font=font,
            clickSound=button_mouseclick_sound)
            
            b.setPos(-1, 1, 0)
            self.dbuttons.append(b)

    

    
    def eventPressAddTagfiler(self):
        photocube.dialogs.dialogService.openAddTagFilter()

    def eventPressNewTagset(self):
        photocube.dialogs.dialogService.openCreateNewTagsetDialog()
        
    def eventPressImportImages(self):
        photocube.dialogs.dialogService.openImportImagesDialog()
        
    def eventPressSettings(self):
        np = aspect2d.attachNewNode('floating settings window')
        photocube.dialogs.dialogService.open_settings()

    def eventPressQuit(self):
        sys.exit(0)




class PluginButtonContainer:

    def __init__(self):
        """
        Plugin containers allows modes to add buttons on the top menu when they are enabled.
        """
        self.np = NodePath('PluginButtonContainer')
        self.buttons = []
        self.updateTask = None

   
    def __placementTask(self, task):
        """
        Task function to keep the position of the menu in correct place
        with repsect to the window aspect.
        """
        if len(self.buttons) == 0:
            self.updateTask = None
            return task.done

        x = 0.55
        for b in self.buttons:
            b.setX(-base.getAspectRatio() + 0.12)
            b.setZ(x)
            x+=0.10
        return task.cont
    
    
    
    def getNp(self):
        """
        Getter function for the PluginButtonContainer nodepath.
        """
        return self.np
   

    
    def createButton(self, title, event):
        """
        Function for creating new button. The paremters are
        title, the label on the button, and event, call back function that
        is called when the button is clicked.
        """
        button = self.__createButton(title, event)
        self.buttons.append(button)
        return button

    
    
    def reloadButtons(self):
        """
        """
        # Remove all the buttons
        for button in b: b.remove()
        
        # Create the buttons again.
        pass

    
    
    def clearButtons(self):
        """
        """
        if DEBUG: print '--clearing plugin buttons.'
        # Remove all the buttons from the scene graph.
        for button in self.buttons:
            button.remove()

        # initalize our button list.
        self.buttons = list()

    
    
    def __createButton(self, text, clickEventFunction):
        """
        Docstring for __createButton.
        """
        # If there is no task running, we start a new task.
        if self.updateTask is None:
            self.updateTask = taskMgr.add(self.__placementTask, 'PluginButtonPlacementTask')

        loc = 0.96
        self.dbuttons = []
        b = DirectButton(
            text_fg=(1,1,1,0.8), 
            frameColor=(0.4, 0.4, 0.4, 0.8),
            relief=DGG.RAISED, 
            text=(text,text,text,""), 
            pressEffect=1, 
            #scale=0.030, 
            frameSize=(-3.6, 3.6, -0.8, 1.2),
            #frameSize=(-2, 2, -2, 2),
            #text_scale = (1.1),
            text_font = font,
            command=clickEventFunction, 
            rolloverSound=None,
            clickSound=button_mouseclick_sound,
            )
        #b.setScale(0.1, 2, 0.021)
        b.setScale(0.040)
        return b


top_menu = MainButtonContainer()

pluginButtonContainer = PluginButtonContainer()