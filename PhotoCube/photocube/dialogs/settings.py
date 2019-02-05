from pandac.PandaModules import TransparencyAttrib
from direct.gui.DirectGui import *
from pandac.PandaModules import WindowProperties
from photocube.common.gui import createLabel
from abstract import AbstractDialog


class SettingsDialog(AbstractDialog):
    def __init__(self):
        # Call the parent constructor.
        AbstractDialog.__init__(self, aspect2d.attachNewNode('SettingsDialog'))

        # settings to alter
        self.new_screen_resolution = None
        self.new_screen_fullscreen = None

        # Initalize the dialog.
        self.__init_components()        

    def __init_components(self):
        # Set the size of the background image for this dialog.
        self.bg.setScale(0.60, 1 ,0.40)
        
        # Create ok and cancel buttons
        self.create_ok_cancel_buttons()
        self.set_ok_button_pos((0.32, 1, -0.32))
        self.set_cancel_button_pos((0.45, 1, -0.32))

        # Create label for the window
        createLabel(parent=self.np, text='Settings', fg=(1,1,1,0.4), scale=0.030, pos=(0, 0.34))

        # Get all posible screen resoluton.
        sizes = ['800x600', '1024x768', '1224x768', '1280x800', '1280x720', ' 1440x900']

        # find the resolution in the list to set it in the dialog.
        currSize = '%sx%s' % (base.win.getXSize(), base.win.getYSize())

        # Create label for display settings.
        createLabel(parent=self.np, text='Display settings', fg=(1,1,1,1), scale=(0.040), pos=(-0.40, 0.20))

        # Creat dropdown for ....
        screen_res_menu = DirectOptionMenu(text="options",
            scale=0.060,
            text_scale=0.8,
            items=sizes,
            initialitem=sizes.index(currSize) if currSize in sizes else 0,
            highlightColor=(0.65,0.65,0.65,1),
            command=self.event_resolution_changed,
            parent=self.np,
            rolloverSound=None,
        )

        screen_res_menu.setPos(-0.53,2,0.1)
        fullscreen_items = ['window', 'fullscreen']
        selected_index = 1 if base.win.getProperties().getFullscreen() else 0

        full_screen_menu = DirectOptionMenu(text="options",
            scale=0.040,
            text_scale=0.8,
            items=fullscreen_items,
            initialitem=selected_index,
            highlightColor=(0.65,0.65,0.65,1),
            command=self.event_dropdownfullscreen_changed,
            parent=self.np,
            rolloverSound=None,
        )
        full_screen_menu.setPos(-0.10, 0, 0.01)

    def event_dropdownfullscreen_changed(self, arg):
        if arg == 'fullscreen':
            self.new_screen_fullscreen = True
        else:
            self.new_screen_fullscreen = False

    def event_resolution_changed(self, arg):
        print 'resolution changed to', arg
        self.new_screen_resolution = (int(arg.split('x')[0]), int(arg.split('x')[1]))

    def click_cancel_button(self):
        self.np.remove()
        messenger.send('dialog_closing')

    def click_ok_button(self):
        if self.new_screen_resolution:
            wp = WindowProperties()
            wp.setSize(self.new_screen_resolution[0], self.new_screen_resolution[1])
            base.win.requestProperties(wp)

        if self.new_screen_fullscreen is not None:
            wp = WindowProperties()
            wp.setFullscreen(self.new_screen_fullscreen)
            base.win.requestProperties(wp)

        self.np.remove()
        messenger.send('dialog_closing')

