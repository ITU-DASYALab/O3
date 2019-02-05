"""
This modules contains functions for creating generic Panda3d GUI objects.
"""

#imports
from direct.gui.DirectGui import DirectEntry
from direct.gui.DirectGui import OnscreenText 
from direct.gui.DirectGui import DirectOptionMenu
from direct.gui.DirectGui import OnscreenImage

# Global sounds for components.
mouseclick_sound = loader.loadSfx("static/sounds/mouseclick.wav")
mouseover_sound = loader.loadSfx("static/sounds/mouseover.wav")


def createTextbox(parent=None, width=60, text='', pos=(0,1,0), scale=(0.1), focus=0):
    """docstring for createTextbox"""
    return DirectEntry(text = text,
    initialText=text, 
    numLines=1, 
    focus=focus, 
    width=width,
    clickSound = None,
    rolloverSound = None,
    parent=parent,
    pos=pos,
    scale=scale,
    )


def createLabel(parent=None, text='Label text', fg=None, bg=None, scale=(0.1), pos=(0,1,0) ):
    """docstring for createLabel"""
    return OnscreenText(text = text, fg=fg, bg=bg, parent=parent, scale=scale, pos=pos)
    
def createImage(parent=None, image='Label text', scale=(0.1), pos=(0,1,0)):
    """docstring for createImage"""
    return OnscreenImage(parent=parent, image = image, scale=scale, pos=pos)
    
def createDropDownList( parent=None, text='select item', scale=0.035, text_scale=1, items=list(), initialitem=0, pos=(0,1,0), onSelectChangeCommand=None, frameSize=(0, 20, -0.5, 1), font=None ):
    dropDown = DirectOptionMenu(text=text, 
        scale=scale,
        text_scale=text_scale,
        items=items,
        initialitem=initialitem,
        highlightColor=(0.65,0.65,0.65,1),
        parent=parent,
        clickSound=mouseclick_sound,
        item_clickSound=mouseclick_sound,
        pos=pos,
        command=onSelectChangeCommand,
        frameSize=frameSize,
    )
    return dropDown
    


def createDropDown(np, scale=1, items=[], initialIndex=0, pos=(0,0,0)):
    """docstring for createDropDown"""
    m = DirectOptionMenu(text="options", 
        scale=scale,
        text_scale=0.8,
        items=items,
        initialitem=initialIndex,
        parent=np,
        rolloverSound=None,
        clickSound=mouseclick_sound,
        item_clickSound=mouseclick_sound,
        pos=pos,
    )
    return m
