from direct.gui.OnscreenImage import OnscreenImage
from pandac.PandaModules import TransparencyAttrib
from direct.gui.DirectGui import *


class AbstractDialog():
    def __init__(self, np):
        
        self.close_message = 'dialog_closing'
        
        # Set the np for the dialog
        self.np = np
        self.np.setPos(0,0,0)
        
        # Load sounds for dialogs.
        self.mouseclick_sound = loader.loadSfx("static/sounds/mouseclick.wav")
        self.mouseover_sound = loader.loadSfx("static/sounds/mouseover.wav")
        
        # Load the background image for dialogs.
        self.bg = OnscreenImage(image = 'static/images/box.tif', parent=self.np)
        self.bg.setTransparency(TransparencyAttrib.MAlpha)
        self.bg.setAlphaScale(0.85)
        
        # Member variables
        self.btn_ok = None
        self.btn_cancel = None


    def create_ok_cancel_buttons(self, ok_caption='ok', cancel_caption='cancel'):
        # Create the ok button.
        self.btn_ok = DirectButton(text_fg=(1,1,1,1), 
            frameColor=(0.5, 0.5, 0.5, 1),
            relief=DGG.RAISED, 
            text=(ok_caption, ok_caption, ok_caption, ok_caption),
            pressEffect=1, 
            scale=0.030, 
            frameSize=(-2, 2, -0.5, 1.0),  
            parent=self.np,
            rolloverSound=None,
            clickSound=None,
            command=self.click_ok_button
            )
        
        
        self.btn_cancel = DirectButton(text_fg=(1,1,1,1), 
            frameColor=(0.5, 0.5, 0.5, 1),
            #borderWidth=(0.0,0.0), 
            relief=DGG.RAISED, 
            text=(cancel_caption, cancel_caption, cancel_caption, cancel_caption), 
            pressEffect=1, 
            scale=0.030,
            frameSize=(-2, 2, -0.5, 1.0),  
            command=self.click_cancel_button,
            parent=self.np,
            rolloverSound=None,
            clickSound=None
            )


    
    
    
    def create_ok_button(self):
        self.btn_ok = DirectButton(text_fg=(1,1,1,1), 
            frameColor=(0.5, 0.5, 0.5, 1),
            #borderWidth=(0.0,0.0), 
            relief=DGG.RAISED, 
            text=('ok', 'ok', 'ok', 'ok'), 
            pressEffect=1, 
            scale=0.030, 
            frameSize=(-2, 2, -0.5, 1.0),  
            parent=self.np,
            rolloverSound=None,
            clickSound=None,
            command=self.click_ok_button
            )   


    def set_ok_button_pos(self, pos):
        self.btn_ok.setPos(pos)
    
    def set_cancel_button_pos(self, pos):
        self.btn_cancel.setPos(pos)
        
    
    def click_ok_button(self):
        print 'CALLING BASE VERSION!'
        self.np.remove()
        messenger.send('dialog_closing')
    
    def click_cancel_button(self):
        self.np.remove()
        messenger.send('dialog_closing')
