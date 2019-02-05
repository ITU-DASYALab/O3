#Python imports
import sys

#Panda3d imports
from direct.gui.OnscreenImage import OnscreenImage
from pandac.PandaModules import TransparencyAttrib
from direct.gui.DirectGui import *
from pandac.PandaModules import Point3

#Browser import.
from photocube.common.messages import TAGSET_BTN_CLICK
from photocube.common.messages import HIERARCHY_BTN_CLICK
from photocube.common.messages import SEARCH_BTN_CLICK
from photocube.common.messages import FILTER_BTN_CLICK
from photocube.common.messages import CUBE_MENU_OVERVIEW_X_BUTTON_CLICK
from photocube.common.messages import CUBE_MENU_OVERVIEW_Y_BUTTON_CLICK
from photocube.common.messages import CUBE_MENU_OVERVIEW_Z_BUTTON_CLICK

#Dialog import
from photocube.dialogs import dialogService

# Global variables
BUTTON_FRAME_COLOR = (.3, .3, .3, 1.0)
BUTTON_TEXT_SHADOW = (0,0,0,1)
BUTTON_TEXT_FG = (1,1,1,1)
FRAME_COLOR = (0.3,0.3,0.3,0.6)

ROLLOVERSOUND = base.loader.loadSfx("static/sounds/mouseover.wav")
CLICKSOUND = base.loader.loadSfx("static/sounds/mouseclick.wav")


def make_context_item(label, index, args):
    """
    Function for creating context items.
    Used in the context menu creation functions.
    """
    return DirectButton(text_scale=0.8, text_fg=(1,1,1,1), frameColor=(0.1,0.1,0.1,1), 
        borderWidth=(0,0), relief=DGG.RAISED, 
        text='+'+ label, pressEffect=0, scale=1, 
        frameSize=(-args[1],args[1],-0.5,1.0),
        rolloverSound=ROLLOVERSOUND,
        clickSound=CLICKSOUND,
        command=args[0], extraArgs=[label])


class ContextMenuHandler:
    """
    Constructor for the ContectMenuHandler class.
    Creates all the context menus and hides them.
    Handles message that have to do with context
    menues.
    """
    def __init__(self):
        self.__create_context_menu()
        self.__create_tagset_numerical_context_menu()
        self.__create_tagset_alphanumerical_context_menu()
        self.__create_tagset_alphanumerical_search_context_menu()
        self.__create_tagset_rgb_search_context_menu()
        self.__create_hierarchy_context_menu()
        self.__create_taglistItem_context_menu()        
        self.__create_tagFilterlistItem_context_menu()
        
        # Member variable that holds the current open context menu.
        self.current_open_context_menu = None
        base.accept('CLICK_MOUSE1_None', self.close_open)
        base.accept('CLICK_MOUSE3_None', self.close_open)

    def close_open(self, p=None, x=None):
        """
        this function checks if there are any context menu open,
        if so, then they'll be closed
        """
        if self.current_open_context_menu is not None:
            self.current_open_context_menu.hide()
            self.current_open_context_menu = None
            print 'Closing context menu.'
            # Force repaint for showing the dialog before the images.
            base.graphicsEngine.renderFrame()
            base.graphicsEngine.renderFrame()

    def has_open_context(self):
        """
        Function for askin the context handler if it has open
        context menu, or not.
        """
        return not self.current_open_context_menu is None 

    def open_image_context(self, p=None):
        """
        This function is called when image is right clicked.
        """
        # close previous context menus.
        self.close_open()

        # set the position of the context menu to the location of the mouse.
        self.cluster_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        
        
        self.cluster_context.show()
        self.current_open_context_menu = self.cluster_context
    
    

    def openContext(self, context):
        self.close_open()
        self.current_open_context_menu = context
        self.current_open_context_menu.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        self.current_open_context_menu.show()


    def open_x_view_context(self):
        """
        Function for opening the x_view context
        """
        # close previous context menus.
        self.close_open()
        
        # set the position of the context menu to the location of the mouse.
        self.x_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        
        # Make the context menu visable.
        self.x_context.show()
        self.current_open_context_menu = self.x_context
    
    
    
    
    def open_y_view_context(self):
        """
        Function for opening the x_view context
        """
        # close previous context menus.
        self.close_open()
        
        # set the position of the context menu to the location of the mouse.
        self.y_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        
        # Make the context menu visable.
        self.y_context.show()
        self.current_open_context_menu = self.y_context
  
    
    
    
    def open_z_view_context(self):
        """
        Function for opening the x_view context
        """
        # close previous context menus.
        self.close_open()
        
        # set the position of the context menu to the location of the mouse.
        self.z_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        
        # Make the context menu visable.
        self.z_context.show()
        self.current_open_context_menu = self.z_context
 
 
    
    
    
    def open_context_tagset_numerical(self):
        self.close_open()
        self.numerical_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        self.numerical_context.show()
        self.current_open_context_menu = self.numerical_context
        
        
    
    
    def open_context_tagset_alphanumerical(self):
        self.close_open()
        self.alphanumerical_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        self.alphanumerical_context.show()
        self.current_open_context_menu = self.alphanumerical_context   


    
    def open_context_hierarchy(self):
        self.close_open()
        self.hierarchy_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        self.hierarchy_context.show()
        self.current_open_context_menu = self.hierarchy_context  



    def open_context_tagset_search_alphanumerical(self):
        self.close_open()
        self.alphanumerical_search_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        self.alphanumerical_search_context.show()
        self.current_open_context_menu = self.alphanumerical_search_context   



    def open_context_tagset_search_rgb(self):
        self.close_open()
        self.rgb_search_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        self.rgb_search_context.show()
        self.current_open_context_menu = self.rgb_search_context   
    


    def open_filter_context(self):
        """
        Function for opening the dimension context
        """
        # close previous context menus.
        self.close_open()
        
        # set the position of the context menu to the location of the mouse.
        self.filter_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(),1,base.mouseWatcherNode.getMouse().getY()))
        
        # Make the context menu visable.
        self.filter_context.show()
        self.current_open_context_menu = self.filter_context
    


    def make_context_item(self, label, index, args):
        """
        Function for creating context items.
        Used in the context menu creation functions.
        """
        return DirectButton(text_scale=0.8, text_fg=(1,1,1,1), frameColor=(0.1,0.1,0.1,1), 
            borderWidth=(0,0), relief=DGG.RAISED, 
            text='+'+ label, pressEffect=0, scale=1, 
            frameSize=(-args[1],args[1],-0.5,1.0),
            rolloverSound=ROLLOVERSOUND,
            clickSound=CLICKSOUND,
            command=args[0], extraArgs=[label])
    


    # Begin button handler functions.
    def btn_x_view_click(self, button_label):
        self.close_open()
        #browser.menu.right_menu.btn_x_view(button_label)
        messenger.send(CUBE_MENU_OVERVIEW_X_BUTTON_CLICK, [button_label])
    
    def btn_y_view_click(self, button_label):
        self.close_open()
        messenger.send(CUBE_MENU_OVERVIEW_Y_BUTTON_CLICK, [button_label])
    
    
    def btn_z_view_click(self, button_label):
        self.close_open()
        messenger.send(CUBE_MENU_OVERVIEW_Z_BUTTON_CLICK, [button_label])

    
    def btn_dimensions_click(self, button_label):
        self.close_open()
        #browser.menu.right_menu.btn_dimensions(button_label)
        messenger.send('TAGSET_BTN_CLICK', [button_label])

    
    def btn_hierarchy_click(self, button_label):
        self.close_open()
        messenger.send(HIERARCHY_BTN_CLICK, [button_label])


    def btn_search_click(self, button_label):
        self.close_open()
        messenger.send(SEARCH_BTN_CLICK, [button_label])
        

    def btn_filter_click(self, button_label):
        self.close_open()
        messenger.send(FILTER_BTN_CLICK, [button_label])
        #browser.menu.right_menu.btn_filters(button_label)


    def btn_overview_click(self, index):
        self.close_open()
        if index == 'Reset coordinate rotation':
            browser.common.viewService.reset_coordinate_rotation()
        
        elif index == 'Focus on front':
            browser.common.viewService.reset_coordinate_aim_front()
            
        elif index == 'Focus on up':
            browser.common.viewService.reset_coordinate_aim_up()
        
        elif index == 'Focus on in':
            browser.common.viewService.reset_coordinate_aim_in()
        
        else:
            pass 
    
    
    
    def btn_clusters_click(self, index):
        self.close_open()
        messenger.send('cluster_cell_context_select', [index])
    # end of button handler functions.



    def __create_taglistItem_context_menu( self ):
        button_width = 5
        menu_items = ['remove tag']
        
        self.tagListItems_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-5.1, 5.1, -0.7, 1.15),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = menu_items,
            numItemsVisible=len(menu_items),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_taglistItem_click, button_width]
        )
        self.tagListItems_context.hide()


    def btn_taglistItem_click(self, index):
        self.close_open()
        messenger.send('tagListItemMenuIndexSelect', [index])


    def showTagsetItemContectMenu(self):
        self.close_open()
        self.tagListItems_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(), -2, base.mouseWatcherNode.getMouse().getY()))
        self.tagListItems_context.show()
        self.tagListItems_context.reparentTo(aspect2d)
        self.current_open_context_menu = self.tagListItems_context 





    def __create_tagFilterlistItem_context_menu( self ):
        button_width = 5
        menu_items = ['add tag filter', 'cancel']
        
        self.tagListFilterItems_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-5.1, 5.1, -2.2, 1.15),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = menu_items,
            numItemsVisible=len(menu_items),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_taglistItem_click, button_width]
        )
        self.tagListFilterItems_context.hide()


    def btn_taglistItem_click(self, index):
        self.close_open()
        messenger.send('tagListFilterItemMenuIndexSelect', [index])


    def showTagFilterItemContectMenu(self):
        self.close_open()
        self.tagListFilterItems_context.setPos(render2d,Point3(base.mouseWatcherNode.getMouse().getX(), -2, base.mouseWatcherNode.getMouse().getY()))
        self.tagListFilterItems_context.show()
        self.tagListFilterItems_context.reparentTo(aspect2d)
        self.current_open_context_menu = self.tagListFilterItems_context 







    def __create_hierarchy_context_menu( self ):
        button_width = 5
        menu_items = ['view front', 'view up', 'view in', 'add dimension filter',]
        self.hierarchy_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-5.1,5.1,-5.5,1.2),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = menu_items,
            numItemsVisible=len(menu_items),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_hierarchy_click, button_width]
        )
        self.hierarchy_context.hide()
    

    def __create_tagset_alphanumerical_search_context_menu( self ):
        button_width = 5
        menu_items = ['search']
        self.alphanumerical_search_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-5.1,5.1,-5.5,1.2),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = menu_items,
            numItemsVisible=len(menu_items),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_search_click, button_width]
        )
        self.alphanumerical_search_context.hide()


    def __create_tagset_rgb_search_context_menu( self ):
        button_width = 5
        menu_items = ['search']
        self.rgb_search_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-5.1,5.1,-5.5,1.2),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = menu_items,
            numItemsVisible=len(menu_items),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_search_click, button_width]
        )
        self.rgb_search_context.hide()
    

    def __create_tagset_numerical_context_menu(self):
        items = ['view front', 'view up', "view in", "add range filter", 'add tag filter', 'add dimension filter', 'edit']
        button_width = 5
        self.numerical_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-5.1,5.1, -10.3, 1.2),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = items,
            numItemsVisible=len(items),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_dimensions_click, button_width]
            
        )
        self.numerical_context.hide()
        

    def __create_tagset_alphanumerical_context_menu(self):
        items =  ['view front', 'view up', "view in", "add tag filter", "add dimension filter", "edit"]
        button_width = 5.2
        self.alphanumerical_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-5.35, 5.35, -8.7, 1.2),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = items,
            numItemsVisible=len( items ),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_dimensions_click, button_width]
        )
        self.alphanumerical_context.hide()
    
    
    
    
    
    def __create_context_menu(self):

        
        # create context menu for x
        button_width = 3.5
        self.x_context = DirectScrolledList(text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-3.7,3.7,-8.6,1.1),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,
            scale=0.035,
            items = ['view up', 'view in', 'swap with up', 'swap with in', 'clear', 'Cancel'],
            numItemsVisible=6,
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_x_view_click, button_width]
            
        )
        self.x_context.hide()
        
        

        # create context menu for y
        self.y_context = DirectScrolledList(
        text_fg=(1,1,1,1), 
        text_shadow=(0,0,0,1), 
        frameColor=FRAME_COLOR, 
        frameSize=(-3.7,3.7,-8.6,1.1),
        borderWidth=(0.1,0.1), 
        relief=DGG.RIDGE, 
        text="", 
        forceHeight=1.6,
        scale=0.035,
        items = ['view up',"view front",'swap with up',"swap with front","clear","Cancel"],
        numItemsVisible=6,
        parent=aspect2d,
        itemMakeFunction=self.make_context_item,
        itemMakeExtraArgs=[self.btn_y_view_click, button_width]
        )
        self.y_context.hide()
        
        # create context menu for z
        self.z_context = DirectScrolledList(
        text_fg=(1,1,1,1), 
        text_shadow=(0,0,0,1), 
        frameColor=FRAME_COLOR, 
        frameSize=(-3.7,3.7,-8.6,1.1),
        borderWidth=(0.1,0.1), 
        relief=DGG.RIDGE, 
        text="", 
        forceHeight=1.6,
        scale=0.035,
        items = ['view front',"view in",'swap with front',"swap with in","clear","Cancel"],
        numItemsVisible=6,
        parent=aspect2d,
        itemMakeFunction=self.make_context_item,
        itemMakeExtraArgs=[self.btn_z_view_click, button_width])
        self.z_context.hide()       

        
        
        
        
        # create context menu for filters
        button_width = 3.5
        self.filter_context = DirectScrolledList(
            text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=FRAME_COLOR, 
            frameSize=(-3.65, 3.65, -0.7, 1.1), 
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE, 
            text="", 
            forceHeight=1.6,   # Height of each item - needed for all ScrolledLists
            scale=0.035,
            items = ['remove filter'],   # Strings here mean that function will be called to make items
            numItemsVisible=3,  # All items visible, otherwise scrolling will be needed
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_filter_click, button_width]            
            ) # This is the function for creating items
        self.filter_context.hide()       

        
        
        
        
        # create context overview
        button_width = 2
        self.overview_context = DirectScrolledList(
        text_fg=(1,1,1,1), 
        text_shadow=(0,0,0,1), 
        frameColor=FRAME_COLOR, 
        frameSize=(-6.5,6.5,-7.2,1.5),
        borderWidth=(0.1,0.1), 
        relief=DGG.RIDGE, 
        text="", 
        forceHeight=1.6,
        scale=0.035,
        items = ['Reset coordinate rotation',"Focus on front", "Focus on up", "Focus on in", "Cancel"],
        numItemsVisible=5,
        parent=aspect2d,
        itemMakeFunction=self.make_context_item,
        itemMakeExtraArgs=[self.btn_overview_click, button_width] 
        )
        self.overview_context.hide()


        # create context for image clusters.
        button_width = 4
        frame_width = 4.2
        frame_height = 2
        items = ['add tag to cell', 'select cell']

        self.cluster_context = DirectScrolledList(
            text_fg=(1,1,1,1), 
            text_shadow=(0,0,0,1), 
            frameColor=(0.2,0.2,0.2,0.9), 
            frameSize=(-frame_width, frame_width, -2.3, 1.1),
            borderWidth=(0.1,0.1), 
            relief=DGG.RIDGE,
            text="", 
            forceHeight=1.7,
            scale=0.035,
            items = items,
            numItemsVisible=len(items),
            parent=aspect2d,
            itemMakeFunction=self.make_context_item,
            itemMakeExtraArgs=[self.btn_clusters_click, button_width] 
        )
        self.cluster_context.hide()

context_menu_handler = ContextMenuHandler()
