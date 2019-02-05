from ObjectCubePython import *
from ObjectCubePython import Hub, State

import sys
import re
import panda3d
#sys.path.append('/Developer/Panda3d/lib')
sys.path.append('/usr/share/panda3d')
sys.path.append('/usr/local/lib')

from pandac.PandaModules import loadPrcFileData

# Change the panad3d window title.
loadPrcFileData("", "window-title " + 'PhotoCube')
loadPrcFileData("", """text-encoding utf8""")

import direct.directbase.DirectStart
from pandac.PandaModules import WindowProperties

from photocube.configuration import browser_config
from photocube.common import error_output
from photocube.constants import DEFAULT_BACKGROUND_COLOR, DEFAULT_RESOLUTION, DEFAULT_FULLSCREEN
import photocube.modes

if __name__ == '__main__':
    # Check if there is a configuration for the bg color. If not
    # we use the default color in background.
    _background_color = DEFAULT_BACKGROUND_COLOR
    if 'background_color' in browser_config.getConfigKeys():
        color = browser_config.getValue('background_color')
        
        # Check the format of the background color. It should be a triplet
        # with three number elements.
        if re.match('^(\d(.\d+)?,\d(.\d+)?,\d(.\d+)?)$', color):
            colors = tuple(color.split(','))
            _background_color = (float(colors[0]), float(colors[1]), float(colors[2]))
        else:
            error_output('illegal form for the background color in the configuration.', prefix='Runner')
            sys.exit(0)

    base.setBackgroundColor( _background_color )
    
    
    # Check if we have any screen resolution in our configuration file, if not we use default. 
    (sx, sy) = DEFAULT_RESOLUTION.split('x')

    if 'screen_resolution' in browser_config.getConfigKeys():
        resValue = browser_config.getValue('screen_resolution')
        (sx, sy) = ( int(resValue.split('x')[0]), int(resValue.split('x')[1]) )  
    #
    ## Set the screen resolution.
    wp = WindowProperties()
    
    # Check if we have any fullscreen mode in the configuration.
    _fullscreen = DEFAULT_FULLSCREEN
    if 'fullscreen' in browser_config.getConfigKeys():
        _fullscreen = bool( int(browser_config['fullscreen']) )
    
    wp.setFullscreen( _fullscreen )
    wp.setSize(int(sx), int(sy))
    base.win.requestProperties(wp)

    # Disable panda3d mouse handler.
    base.disableMouse()
    
    # Initialize the browser in cubemode.
    photocube.modes.cubeMode.enable()
    
    # Start Panda3D event loop.
    run()
