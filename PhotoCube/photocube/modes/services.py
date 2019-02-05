from pandac.PandaModules import NodePath
from pandac.PandaModules import TextNode

from photocube.ui.coremenu import pluginButtonContainer
from photocube.modes.mode import *
import photocube.image



# MESSEGES SENT FROM THIS PACKAGE
#################################################################
RELOAD_FILTER_MENU_MESSAGE = 'FILTER_MENU_RELOAD'
#################################################################



#################################################################
class ModeServiceException(Exception):
    def __init__(self, value):
        self.parameter = value
    
    def __str__(self):
        return repr(self.parameter)
#################################################################



#################################################################
class ModeService:
    """
    This class handles the browsing view modes.
    """
    
    def __init__(self):
        self.current_mode = None
        print '[ModeService]', 'instance created'
        
        # Dictionary for registered modes. Keys are enable_keys set in the mode.
        self.modes = dict()
        
        # Receive
        base.accept( 'change-mode', self.change_mode )

        self.__createCurrentModeLabel()
        base.taskMgr.add(self.__currentModeLabelPositionTask, 'Currentmodelabeltask')


    
       
    def __createCurrentModeLabel(self):
        self.text = TextNode('node name')
        self.text.setText("Current mode: None")
        self.textNodePath = aspect2d.attachNewNode(self.text)
        self.textNodePath.setScale(0.03)
        self.textNodePath.setX(-base.getAspectRatio()-0.2)
        self.textNodePath.setZ(-0.95)


    def __currentModeLabelPositionTask(self, task):
        self.textNodePath.setX(-base.getAspectRatio()+0.05)
        self.textNodePath.setZ(-0.95)
        return task.cont
       
    
    
    def enable_default_mode(self):
        self.modes['CubeMode'].enable()
    
    
    
    def get_current_mode(self):
        """
        """
        return self.current_mode
        
    
    def register_mode(self, mode):
        """
        """
        if mode.get_mode_name() in self.modes.keys():
            raise ModeServiceException('Mode with name "' + mode.get_name() + '" is already is already registered.')
        else:
            self.modes[ mode.get_mode_name() ] = mode
            print 'registering mode', mode.get_mode_name(), 'with key', mode.get_enable_key()
            
    
    

    def change_mode(self, args):
        #if browser.dialogs.dialogService.hasOpenDialog():
        #    return
        print 'request for changing mode!', args
        
        selected_mode = self.modes[ args ]
        
        if self.current_mode is not None:
            if self.current_mode != selected_mode:
                # clear the buttons that the last mode might have added.
                pluginButtonContainer.clearButtons()
                
                self.current_mode.disable()
                selected_mode.initalize()
        else:
            selected_mode.initalize()        

        self.current_mode = selected_mode
        self.text.setText('Current mode: ' + selected_mode.get_mode_name())
        
        
        # Load the mode and pass the cube into it.
        self.current_mode.load( photocube.cube.cubeService.getCurrentCube() )
#################################################################

