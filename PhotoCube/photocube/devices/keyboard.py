from direct.task import Task
from math import *
from sys import exit 
from pandac.PandaModules import WindowProperties
from photocube.configuration import browser_config
from photocube.dialogs import dialogService


"""
General keyboard handling.
"""

class KeyboardHandler:
    
    """
    KeyboardHandler handles all keyboard events.
    """

    def __init__(self, enable_default=True):
        """
        Constructor for the KeyboardHandler class.
        """
        
        # These messages will always be available
        if enable_default:
            base.accept('q', self.browserQuit)
            base.accept('o', self.toggleFullScreen)

        
    def toggleFullScreen(self):
        # If there is an open dialog, then this function
        # will not execute.
        if dialogService.hasOpenDialog():
            return
        
        wp = WindowProperties()
        
        if not browser_config['fullscreen']:
            wp.setSize(base.win.getXSize(), base.win.getYSize())
            wp.setFullscreen(True)
            base.win.requestProperties(wp)
            browser_config['fullscreen'] = True
        
        else:
            wp.setSize(base.win.getXSize(), base.win.getYSize())
            wp.setFullscreen(False)
            base.win.requestProperties(wp)
            browser_config['fullscreen'] = False

  
    def browserQuit(self):
        # If there is an open dialog, then this function
        # will not execute.
        if not dialogService.hasOpenDialog():
            exit()
