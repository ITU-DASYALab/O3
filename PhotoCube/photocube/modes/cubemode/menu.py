#Python import
import sys

#Panda3d import
from direct.gui.OnscreenImage import OnscreenImage
from pandac.PandaModules import TransparencyAttrib
from direct.gui.DirectGui import *
from pandac.PandaModules import TextNode
from pandac.PandaModules import CardMaker
from pandac.PandaModules import Point3

#Browser import
import photocube.dialogs
import photocube.cube
import photocube.devices
from photocube.devices import mouse_handler

from photocube.common import X_AXIS, Y_AXIS, Z_AXIS
from photocube.common.messages import CUBE_MENU_RELOAD_FILTERS
from photocube.common.messages import TAGSET_BTN_CLICK
from photocube.common.messages import HIERARCHY_BTN_CLICK
from photocube.common.messages import SEARCH_BTN_CLICK
from photocube.common.messages import FILTER_BTN_CLICK
from photocube.common.messages import CUBE_MENU_OVERVIEW_X_BUTTON_CLICK
from photocube.common.messages import CUBE_MENU_OVERVIEW_Y_BUTTON_CLICK
from photocube.common.messages import CUBE_MENU_OVERVIEW_Z_BUTTON_CLICK
from photocube.common.messages import CUBE_MENU_RELOAD_DIMENSIONS
from photocube.actions import ActionTagset
from photocube.actions import ActionHierachy
from photocube.actions import ActionAxis
from photocube.actions import actionManager
from photocube.actions import ActionFilter

# Import action types.
from photocube.actions import ACTION_DELETE, ACTION_SET, ACTION_MOVE, ACTION_SWAP, ACTION_CLEAR, ACTION_ADD

# Improt action names.
from photocube.actions import ACTION_TAGFILTER, ACTION_DIMENSIONFILTER

#Python import.
import math

#ObjectCube import
sys.path.append( '../ObjectCube' )
import ObjectCubePython
from photocube.objectcube import filterManager
from photocube.ui.coremenu.abstract import AbstractMenu

EMPTY_ON_FRONT = 'front: empty'
EMPTY_ON_IN = 'in: empty'
EMPTY_ON_UP = 'up: empty'

from photocube.ui.sounds import button_mouseclick_sound as button_mouseclick_sound


class RightMenu:
    """
    Add comment.
    """
    def __init__(self):

        self.visible_x_np = None
        self.visible_y_np = None
        self.visible_z_np = None
        
        self.filter_label_np = None
        self.dims_parent_np = None       
        
        # Dictionary for the tagset/dims
        self.dimensionCards = {}
        
        # Member variable for dimension/filter context menu.
        self.selected_tagset_id = None
        self.selected_hierarchy_id = None        
        self.selected_filter_id = None

        # Create nodepath for the menu.
        self.right_menu_node_path = camera.attachNewNode('right_menu_node_path')
        self.right_menu_node_path.setY(3)
                
        # Flag for right menu visability.
        self.is_visable = True
        
        # Create background for the menu.
        self.bg = OnscreenImage(image = 'static/images/box.tif')
        self.bg.setTransparency(TransparencyAttrib.MAlpha)
        self.bg.setAlphaScale(0.24)
        self.bg.setScale(1, 2, 2)
        
        # start the placement task for menu placement.
        base.taskMgr.add(self.__placement, 'menuplacement_left_panel')

        
        # Collections of cards. Used for card highlighting.
        self.cards = dict()
        
        # How many dimensions should we show in the dimension list?
        self.max_dimension_visable_in_menu = 10
                
        # Member variable for the dimensions scrollbar if needed.
        self.dimension_scrollbar = None
        
        # Create all the objects for this menu.
        self.__initalize_objects()
        self.__createTagsetAndHierarchyLabels()
        self.__register_view_menu_messages()
                
        # Create instance of filter menu.
        self.filter_menu = FilterMenu(np=self.right_menu_node_path, begin_pos = self.last_dim_pos)

        # Events that we are interested in.
        base.accept(CUBE_MENU_RELOAD_FILTERS, self.reload_filter2)
        base.accept(TAGSET_BTN_CLICK, self.btn_dimensions)
        base.accept(HIERARCHY_BTN_CLICK, self.btn_hierarchy)
        base.accept(SEARCH_BTN_CLICK, self.btn_search)
        base.accept(FILTER_BTN_CLICK, self.btn_filters)
        base.accept(CUBE_MENU_OVERVIEW_X_BUTTON_CLICK, self.btn_x_view)
        base.accept(CUBE_MENU_OVERVIEW_Y_BUTTON_CLICK, self.btn_y_view)
        base.accept(CUBE_MENU_OVERVIEW_Z_BUTTON_CLICK, self.btn_z_view)
        base.accept(CUBE_MENU_RELOAD_DIMENSIONS, self.reloadDimensionLabels)
    

    def reloadDimensionLabels(self):
        """
        Function for reloading the tagset/hir list.
        This function is called when tagset/hir is changed
        or new are added.
        """
        self.__createTagsetAndHierarchyLabels()
        #self.reload()
        
    
    def __createTagsetAndHierarchyLabels(self):
        if self.dims_parent_np is not None:
            self.dims_parent_np.remove()
        
        if self.dimension_scrollbar is not None:
            self.dimension_scrollbar.remove()


        # Create labels for each tagset and hirs.
        card_pos = -1.1
        index = 0 
        
        # List that contains the dimension cards. Used for scrolling the cards.
        self.dimension_list = [] 
        
        #self.cards = dict()
        
        self.dims_parent_np = self.right_menu_node_path.attachNewNode('parent_dim_np') 

        for tagset in photocube.objectcube.objectCubeService.getAllTagsets():
            if (tagset.typeId == 1 or tagset.typeId == 5) and (tagset.name[:5] != 'Rank:' and tagset.name[:5] != 'Dist:'): #FOR MASTER PRESENTATION, NOT SHOWING SEARCH DIMENSION
                #print 'tagset.name: ' + tagset.name + 'tagset.typeId: ' + str(tagset.typeId)
                dim_np = self.dims_parent_np.attachNewNode('dim;tagset;' + str(tagset.id))
          
                # Create a card to make the dimension clickable
                card_np = dim_np.attachNewNode('card-tagset-'+ tagset.name)
                card_np = card_np.attachNewNode('card-x-label-np')
                card_np.setPos(1,1.5,1.5)
                cm = CardMaker('card')
                card = card_np.attachNewNode(cm.generate())
                card.setScale(0.50, 1, 0.050)
                card.setPos(-2.045, -1.3, card_pos)
                card.setTwoSided(True)
                card.setColor(0,0,0)
                
                # Make the tagset cards clickable.
                base.accept(photocube.devices.mouse_handler.makeNPPickableRight(dim_np), self.on_tagset_right_click)
                base.accept(photocube.devices.mouse_handler.makeNPPickableLeft(dim_np), self.on_tagset_right_click)
                
                # Create a new node for the text label.
                t_node = card.attachNewNode( 'card-label' + tagset.name )
                t_node.setY(-0.001)
                t_node.setZ(1.35)
                t_node.setX(0.03)
                
                t = OnscreenText(text=tagset.name[0:43] + ' (tagset)', fg=(1,1,1,1), parent=t_node, pos=(0, -1, -4), scale=(0.075, 0.73), align=TextNode.ALeft)

                # Make the dim button mouse over enabled.
                if dim_np.__str__() not in self.cards.keys():
                    self.cards[ dim_np.__str__() ] = card
                
                self.dimension_list.append( dim_np )
                messageHover,messageLeave  = photocube.devices.mouse_handler.makeNPMouseHoverable( dim_np )

                
                # When created, the menu is hided.
                dim_np.hide()
                
                # Accept the hover messages.
                base.accept(messageLeave, self.mouse_leave)
                base.accept(messageHover, self.mouse_over)
                
            """
            dim_np = self.dims_parent_np.attachNewNode('dim;tagset;' + str(tagset.id))
          
            # Create a card to make the dimension clickable
            card_np = dim_np.attachNewNode('card-tagset-'+ tagset.name)
            card_np = card_np.attachNewNode('card-x-label-np')
            card_np.setPos(1,1.5,1.5)
            cm = CardMaker('card')
            card = card_np.attachNewNode(cm.generate())
            card.setScale(0.50, 1, 0.050)
            card.setPos(-2.045, -1.3, card_pos)
            card.setTwoSided(True)
            card.setColor(0,0,0)
            
            # Make the tagset cards clickable.
            base.accept(photocube.devices.mouse_handler.makeNPPickableRight(dim_np), self.on_tagset_right_click)
            base.accept(photocube.devices.mouse_handler.makeNPPickableLeft(dim_np), self.on_tagset_right_click)
            
            # Create a new node for the text label.
            t_node = card.attachNewNode( 'card-label' + tagset.name )
            t_node.setY(-0.001)
            t_node.setZ(1.35)
            t_node.setX(0.03)
            
            t = OnscreenText(text=tagset.name[0:43] + ' (tagset)', fg=(1,1,1,1), parent=t_node, pos=(0, -1, -4), scale=(0.075, 0.73), align=TextNode.ALeft)

            # Make the dim button mouse over enabled.
            if dim_np.__str__() not in self.cards.keys():
                self.cards[ dim_np.__str__() ] = card
            
            self.dimension_list.append( dim_np )
            messageHover,messageLeave  = photocube.devices.mouse_handler.makeNPMouseHoverable( dim_np )

            
            # When created, the menu is hided.
            dim_np.hide()
            
            # Accept the hover messages.
            base.accept(messageLeave, self.mouse_leave)
            base.accept(messageHover, self.mouse_over)
            """
            # show the hir
            if tagset.name[:5] != 'Rank:' and tagset.name[:5] != 'Dist:': #FOR MASTER PRESENTATION, NOT SHOWING SEARCH DIMENSION
                for hir in tagset.getPersistentDimensions():
                    
                    hir_np = self.dims_parent_np.attachNewNode('dim;hir;' + tagset.name + ';' + str(hir.id) + ';' + str(tagset.id))
                    
                    # Create a card to make the dimension clickable
                    card_np = hir_np.attachNewNode('card-tagset-'+ tagset.name)
                    card_np = card_np.attachNewNode('card-x-label-np')
                    card_np.setPos(1,1.5,1.5)
                    cm = CardMaker('card-hir')
                    card = card_np.attachNewNode(cm.generate())
                    card.setScale(0.50, 1, 0.050)       
                    card.setPos(-2.045, -1.3, card_pos)
                    card.setTwoSided(True)
                    card.setColor(0,0,0)
                    
                    # Make the hierachy card clickable.                
                    base.accept(photocube.devices.mouse_handler.makeNPPickableRight(hir_np), self.on_hierarchy_right_click)
                    base.accept(photocube.devices.mouse_handler.makeNPPickableLeft(hir_np), self.on_hierarchy_right_click)
                    
                    # Make the hierachy card hoverable.  
                    messageHover,messageLeave = photocube.devices.mouse_handler.makeNPMouseHoverable(hir_np)
                    base.accept(messageHover, self.mouse_over)
                    base.accept(messageLeave, self.mouse_leave)
                    
                    # Create a new node for the text label.
                    t_node = card.attachNewNode( 'card-label' + tagset.name )
                    t_node.setY(-0.001)
                    t_node.setZ(1.35)
                    t_node.setX(0.03)
                
                    t = OnscreenText(text=hir.getRoot().name + ' (hierarchy)', fg=(1,1,1,1), parent=t_node, pos=(0, -1, -4), scale=(0.075, 0.73), align=TextNode.ALeft)
                    
                    # Make the dim button mouse over enabled.
                    if hir_np.__str__() not in self.cards.keys():
                        self.cards[ hir_np.__str__() ] = card
                    
                    self.dimension_list.append( hir_np )
                    photocube.devices.mouse_handler.makeNPMouseHoverable(hir_np)
                    



        # Create label for filters
        if len(self.dimension_list) < self.max_dimension_visable_in_menu:
            self.last_dim_pos = -0.025 * len(self.dimension_list)
            
        else:
            self.last_dim_pos = -0.25
            self.dimension_scrollbar = DirectScrollBar(range=(0, math.ceil(len(self.dimension_list))), orientation= DGG.VERTICAL, command=self.on_dimension_scroll_change, scrollSize=5, pageSize=len(self.dimension_list)/5, value=0)
            
            self.dimension_scrollbar.setScale(0.5, 1 , 0.69)
            self.dimension_scrollbar['frameColor'] = (0.6,0.6,0.6,0.8)
            
            # disable the click sound for the scrollbar.
            self.dimension_scrollbar['incButton_clickSound'] = button_mouseclick_sound
            self.dimension_scrollbar['incButton_rolloverSound'] = None
            self.dimension_scrollbar['decButton_clickSound'] = button_mouseclick_sound
            self.dimension_scrollbar['decButton_rolloverSound'] = None
            self.dimension_scrollbar['thumb_clickSound'] = None
            self.dimension_scrollbar['thumb_rolloverSound'] = None
            self.dimension_scrollbar['incButton_relief'] = None
            self.dimension_scrollbar['decButton_relief'] = None
            self.dimension_scrollbar['decButton_text'] = '-'
            self.dimension_scrollbar['decButton_text_scale']=0.07
            self.dimension_scrollbar['incButton_text'] = '+'
            self.dimension_scrollbar['incButton_text_scale']=(0.07,0.05)
            self.dimension_scrollbar['incButton_text_pos'] = (-0.005,-0.02)
            self.dimension_scrollbar['decButton_text_pos'] = (-0.005,-0.02)
            self.dimension_scrollbar['thumb_frameColor'] = (0, 0, 0, 0.2)
            self.dimenion_scroll_value = self.dimension_scrollbar['value'] 

                    
        self.text_dims = OnscreenText(mayChange=True, text='Filters:',fg=(1,1,1,1),parent=self.right_menu_node_path, pos=(-1.10, self.last_dim_pos, -10), scale=(0.040), align=TextNode.ALeft)

        
        # create nodepath for the filter labels
        self.filter_label_np = self.right_menu_node_path.attachNewNode('filter-label-np')
            
        self.current_dimension_index_left = 0
        self.current_dimension_index_right = self.max_dimension_visable_in_menu - 1
        self.show_dimension_tabs()


    def __initalize_objects(self):
        # refactored from the function for dims labels reload
        self.text_dims = OnscreenText(text='Dimensions:',fg=(1,1,1,1), parent=self.right_menu_node_path, pos=(-1.10, 0.45, -10), scale=0.040, align=TextNode.ALeft)
        
        
        # Create a label for the menu.
        self.text_dims = OnscreenText(mayChange=True, text='Visible:',fg=(1,1,1,1),parent=self.right_menu_node_path, pos=(-1.10, 0.74, -10), scale=(0.040), align=TextNode.ALeft)
        
        self.visible_x_np = self.right_menu_node_path.attachNewNode('np_visiable_x')
        self.visible_x_np.setPos(-0.50, 0, 0.85)
        self.visible_x_np.setScale(0.6)

        
        self.text_x = OnscreenText(mayChange=True, 
            text=EMPTY_ON_FRONT,
            fg=(1,1,1,1),
            parent=self.visible_x_np,
            align=TextNode.ALeft, 
            pos=(-0.95,-0.29, -0.21 ),
            scale=0.075
        )

        
        # Create clicable card for x.        
        card_np = self.visible_x_np.attachNewNode('card-x-label-np').attachNewNode('card-x-label-np')
        card_np.setPos(1,1.5,1.5)
        cm = CardMaker('card-x')
        card = card_np.attachNewNode(cm.generate())
        card.setScale(0.8, 1, 0.1)        
        card.setPos(-1.93, -1.3, -1.78)
        card.setTwoSided(True)
        card.setColor(0,0,0)
        
        # Make the x view nodepath clickable.
        self.curXDimRightClickMessage = mouse_handler.makeNPPickableRight(self.visible_x_np)
        self.curXDimLeftClickMessage = mouse_handler.makeNPPickableLeft(self.visible_x_np)
        
        # Make the x view nodepath mouseoverable and save the nodepath for making it glow.
        self.cards[ self.visible_x_np.__str__() ] = card
        leavemessage,hoverMessage  = photocube.devices.mouse_handler.makeNPMouseHoverable(self.visible_x_np)
        base.accept(hoverMessage, self.mouse_leave)
        base.accept(leavemessage, self.mouse_over)   

        
        # Create notepath for y
        self.visible_y_np = self.right_menu_node_path.attachNewNode('np_visiable_y')
        self.visible_y_np.setPos(-0.50, 0, 0.78)
        self.visible_y_np.setScale(0.6)

        self.text_y = OnscreenText(mayChange=True, 
            text=EMPTY_ON_IN,
            fg=(1,1,1,1),
            parent=self.visible_y_np,
            align=TextNode.ALeft,
            pos=(-0.95, -0.29, 0.21),
            scale=0.075
        )
 

        # Create clicable card for y.        
        card_np = self.visible_y_np.attachNewNode('card-y-label-np').attachNewNode('card-y-label-np')
        card_np.setPos(1,1.5,1.5)
        cm = CardMaker('card-y')
        card = card_np.attachNewNode(cm.generate())
        card.setScale(0.8, 1, 0.1)
        card.setPos(-1.93, -1.3, -1.78)
        card.setTwoSided(True)
        card.setColor(0,0,0)
        card.setTransparency(TransparencyAttrib.MAlpha)
        
        self.curYDimRightClickMessage = mouse_handler.makeNPPickableRight(self.visible_y_np)
        self.curYDimLeftClickMessage = mouse_handler.makeNPPickableLeft(self.visible_y_np)
        
        # Make the y view nodepath mouseoverable.
        self.cards[ self.visible_y_np.__str__() ] = card
        #TODO: Here is a good place to refactor.
        photocube.devices.mouse_handler.makeNPMouseHoverable(self.visible_y_np)
        base.accept('zoomout_render/camera/right_menu_node_path/np_visiable_y', self.mouse_leave)
        base.accept('zoomin_render/camera/right_menu_node_path/np_visiable_y', self.mouse_over)   


        # Create notepath for z
        self.visible_z_np = self.right_menu_node_path.attachNewNode('np_visiable_z')
        self.visible_z_np.setPos(-0.50, 0, 0.71)
        self.visible_z_np.setScale(0.6)

        self.text_z = OnscreenText(mayChange=True, 
        text=EMPTY_ON_UP,
        fg=(1,1,1,1),
        parent=self.visible_z_np,
        align=TextNode.ALeft,
        pos=(-0.95, -0.28, 0.21),
        scale=0.075
        )
 
        
        # Create clicable card for y.        
        card_np = self.visible_z_np.attachNewNode('card-z-label-np').attachNewNode('card-z-label-np')
        card_np.setPos(1,1.5,1.5)
        cm = CardMaker('card-z')
        card = card_np.attachNewNode(cm.generate())
        card.setScale(0.8, 1, 0.1)
        card.setPos(-1.93, -1.3, -1.78)
        card.setTwoSided(True)
        card.setColor(0,0,0)
        card.setTransparency(TransparencyAttrib.MAlpha)
        self.curZDimRightClickMessage = mouse_handler.makeNPPickableRight(self.visible_z_np)
        self.curZDimLeftClickMessage = mouse_handler.makeNPPickableLeft(self.visible_z_np)
        
        # Make the z view nodepath mouseoverable.
        self.cards[ self.visible_z_np.__str__() ] = card
        photocube.devices.mouse_handler.makeNPMouseHoverable(self.visible_z_np)
        base.accept('zoomout_render/camera/right_menu_node_path/np_visiable_z', self.mouse_leave)
        base.accept('zoomin_render/camera/right_menu_node_path/np_visiable_z', self.mouse_over)   
        


        
    
    def on_dimension_scroll_change(self):
        val = int(self.dimension_scrollbar['value'])
        #print 'val', val

        if val == self.dimenion_scroll_value:
            return
        
        elif val < self.dimenion_scroll_value:
            for n in range(self.dimenion_scroll_value - val):
                self.dim_menu_move_up()
        
        else:
            for n in range(val - self.dimenion_scroll_value):
                self.dim_menu_move_down()
        
        
        #self.dimenion_scroll_value = self.dimension_scrollbar['value']
        self.dimenion_scroll_value = val
    
    
    def show_dimension_tabs(self):
        card_pos = 0
        i = 0
        for card in self.dimension_list:
            card.hide()
            card.setX(100)
        
        
        for r in range(self.current_dimension_index_left, len( self.dimension_list )):
            self.dimension_list[r].show()
            self.dimension_list[r].setZ(card_pos)
            self.dimension_list[r].setX(0)
            card_pos -= 0.06
            i += 1
            if i is self.max_dimension_visable_in_menu:
                break

    
    def dim_menu_move_down(self):
        r = len( self.dimension_list ) - self.current_dimension_index_right
        if r>1:
            self.current_dimension_index_left += 1
            self.current_dimension_index_right += 1
            self.show_dimension_tabs()

    def dim_menu_move_up(self):
        if self.current_dimension_index_left > 0:
            self.current_dimension_index_left -= 1
            self.current_dimension_index_right -= 1
            self.show_dimension_tabs()        


    def btn_filters(self, index):
        self.filter_menu.btn_filters(index)
    
    
    
    def mouse_over(self, p):
        if not photocube.ui.coremenu.context_menu_handler.has_open_context():
            #print 'here', p
            c = self.cards[ p.__str__() ]
            #print c
            self.current_glowing_card = c
            c.setColor(0.15, 0.15, 0.15)
        
 
    def mouse_leave(self, p):
        if not photocube.ui.coremenu.context_menu_handler.has_open_context():
            c = self.cards[ p.__str__() ]
            c.setColor(0, 0, 0)
            self.current_glowing_card = None
            

    def clear_glow(self, f=None):
        if not photocube.ui.coremenu.context_menu_handler.has_open_context():
            #print 'clear'
            self.clear_all_glowings()
        

    def clear_all_glowings(self):
        for key in self.cards.keys():
            card = self.cards[ key ]
            card.setColor(0, 0, 0)
        
        self.current_glowing_card = None
   
    
    
    
    
    def btn_x_view(self, index):
        self.clear_glow()
        
        if index == 'view up':
            x = photocube.cube.cubeService.coordinate.get_x()
            if x is not None:
                messenger.send('dim_move_to_axis', [X_AXIS, Z_AXIS])
                action = ActionAxis(ACTION_MOVE, X_AXIS, Z_AXIS)
                actionManager.addAction( action )

        if index == 'view in':
            x = photocube.cube.cubeService.coordinate.get_x()
            if x is not None:
                messenger.send('dim_move_to_axis', [X_AXIS, Y_AXIS])
                action = ActionAxis(ACTION_MOVE, X_AXIS, Y_AXIS)
                actionManager.addAction( action )
        
        if index == "swap with up":
            messenger.send( 'x_dim_action_swap', [Z_AXIS] )
            # create action for the swap.
            action = ActionAxis(ACTION_SWAP, X_AXIS, Z_AXIS)
            actionManager.addAction(action)

        if index == "swap with in":
            messenger.send( 'x_dim_action_swap', [Y_AXIS] )
            # create action for the swap.
            action = ActionAxis(ACTION_SWAP, X_AXIS, Y_AXIS)
            actionManager.addAction(action)

        if index is 'clear':
            messenger.send( 'dim_action_clear', [X_AXIS] )
            action = ActionAxis(ACTION_CLEAR, X_AXIS)
            actionManager.addAction(action)
            

    
    
    
    
    
    
    def btn_y_view(self, index):
        """
        This function is called when we select buttons
        in the view y context menu.
        """
        self.clear_glow()
        
        if index == 'clear':
            messenger.send( 'dim_action_clear', [Y_AXIS] )
            action = ActionAxis(ACTION_CLEAR, Y_AXIS)
            actionManager.addAction( action )

        if index == 'view front':
            y = photocube.cube.cubeService.coordinate.get_y()

            if y is not None:
                messenger.send('dim_move_to_axis', [Y_AXIS, X_AXIS])
                action = ActionAxis(ACTION_MOVE, Y_AXIS, X_AXIS)
                actionManager.addAction( action )
            
        if index == 'view up':
            y = photocube.cube.cubeService.coordinate.get_y()

            if y is not None:
                messenger.send('dim_move_to_axis', [Y_AXIS, Z_AXIS])
                action = ActionAxis(ACTION_MOVE, Y_AXIS, Z_AXIS)
                actionManager.addAction( action )
        
        if index == "swap with front":
            messenger.send( 'y_dim_action_swap', [X_AXIS] )
            action = ActionAxis(ACTION_SWAP, Y_AXIS, X_AXIS)
            actionManager.addAction( action )
        
        if index == "swap with up":
            messenger.send( 'y_dim_action_swap', [Z_AXIS] )
            action = ActionAxis(ACTION_SWAP, Y_AXIS, Z_AXIS)
            actionManager.addAction( action )





    def btn_z_view(self, index):
        self.clear_glow()
        
        if index == 'clear':
            messenger.send( 'dim_action_clear', [Z_AXIS] )
            action = ActionAxis(ACTION_CLEAR, Z_AXIS)
            actionManager.addAction( action )
            
        if index == 'view front':
            z = photocube.cube.cubeService.coordinate.get_z()

            if z is not None:
                messenger.send('dim_move_to_axis', [Z_AXIS, X_AXIS])
                action = ActionAxis(ACTION_MOVE, Z_AXIS, X_AXIS)
                actionManager.addAction( action )

        if index == 'view in':
            z = photocube.cube.cubeService.coordinate.get_z()

            if z is not None:
                messenger.send('dim_move_to_axis', [Z_AXIS, Y_AXIS])
                action = ActionAxis(ACTION_MOVE, Z_AXIS, Y_AXIS)
                actionManager.addAction( action )
        
        if index == "swap with front":
            messenger.send( 'z_dim_action_swap', [X_AXIS] )
            action = ActionAxis(ACTION_SWAP, Z_AXIS, X_AXIS)
            actionManager.addAction( action )

        if index == "swap with in":
            messenger.send( 'z_dim_action_swap', [Y_AXIS] )
            action = ActionAxis(ACTION_SWAP, Z_AXIS, Y_AXIS)
            actionManager.addAction( action )

    
    

    
    def btn_dimensions(self, index):
        self.clear_glow()
        tagset = photocube.objectcube.objectCubeService.get_tagset_by_id(self.selected_tagset_id )

        if index == 'view front':
            action = ActionTagset(ACTION_SET, tagset.id, X_AXIS)
            actionManager.addAction(action)
            messenger.send('dim_view_tagset', [X_AXIS, tagset])

        if index == 'view in':
            action = ActionTagset(ACTION_SET, tagset.id, Y_AXIS)
            actionManager.addAction(action)
            messenger.send('dim_view_tagset', [Y_AXIS, tagset])
                    
        if index == 'view up':
            action = ActionTagset(ACTION_SET, tagset.id, Z_AXIS)
            actionManager.addAction(action)
            messenger.send('dim_view_tagset', [Z_AXIS, tagset])

        if index == 'add dimension filter':
            dim_filter = ObjectCubePython.DimensionFilter(tagset.getDefaultDimension().getRoot(), tagset.id)
            filterManager.add_filter( dim_filter, True )
            
            # add action
            action = ActionFilter(ACTION_DIMENSIONFILTER, ACTION_ADD, tagsetId=tagset.id )
            actionManager.addAction(action)
            
            # reload filters menu.
            self.reload_filter2()
        
        if index == 'add tag filter':
            photocube.dialogs.dialogService.open_add_tagfilter(tagset)
        
        if index == 'add range filter':
            if tagset.typeId == 3:
                photocube.dialogs.dialogService.open_add_date_range(tagset)
            
            elif tagset.typeId == 4:
                photocube.dialogs.dialogService.open_add_time_range(tagset)
            
            else:
                photocube.dialogs.dialogService.open_add_numerical_range(tagset)
        
        if index == 'edit':
            photocube.dialogs.dialogService.openCreateNewTagsetDialog(tagset)


    
    
    
    def btn_hierarchy(self, index):
        # Get the tagset that the hir belongs to.
        tagset = photocube.objectcube.objectCubeService.get_tagset_by_id( self.selected_tagset_id )
        print 'selected_hierarchy_id: ' + str(self.selected_hierarchy_id)
        # Get the hirarchy from the tagset.
        dim = tagset.getDimension( int( self.selected_hierarchy_id ))
        print 'Dimension click'
        if index == 'view front':
            print 'DimId: ' + str(dim.id)
            print 'TagSetId: ' + str(tagset.id)
            print index + ': Begin'
            print 'ACTION_SET'
            print ACTION_SET
            print 'X_AXIS'
            print X_AXIS
            action = ActionHierachy(ACTION_SET, tagset.id, dim.id, X_AXIS)
            actionManager.addAction(action)
            print 'action'
            print action
            messenger.send('dim_view_hierarchy', [X_AXIS, dim])
            print index + ': End'
        
        elif index == 'view in':
            action = ActionHierachy(ACTION_SET, tagset.id, dim.id, Y_AXIS)
            actionManager.addAction(action)
            messenger.send('dim_view_hierarchy', [Y_AXIS, dim])

        elif index == 'view up':
            action = ActionHierachy(ACTION_SET, tagset.id, dim.id, Z_AXIS)
            actionManager.addAction(action)
            messenger.send('dim_view_hierarchy', [Z_AXIS, dim])
        
        elif index == 'add dimension filter':
            dim_filter = ObjectCubePython.DimensionFilter(dim.getRoot(), tagset.id)
            filterManager.add_filter( dim_filter, True )
            
            # add action
            action = ActionFilter(ACTION_DIMENSIONFILTER, ACTION_ADD, tagsetId=tagset.id, hirarchyId=int( self.selected_hierarchy_id ) )
            actionManager.addAction(action)
            self.reload_filter2()
        
        else:
            raise Exception( 'btn_hierarchy: unknown index: ' + index )

    def btn_search(self, index):
        tagset = photocube.objectcube.objectCubeService.get_tagset_by_id( self.selected_tagset_id )
        if index == 'search':
            print 'Vuubidu'
            photocube.dialogs.dialogService.openSearchDialogWithTagSet(tagset)
    
    def reload_filter2(self):
        self.filter_menu.reload()

    def on_x_view_right_click(self, f):
        photocube.ui.coremenu.context_menu_handler.open_x_view_context()

    def open_context_view_y(self, f):
        photocube.ui.coremenu.context_menu_handler.open_y_view_context()

    def open_context_view_z(self, f):
        photocube.ui.coremenu.context_menu_handler.open_z_view_context()


    def on_hierarchy_right_click(self, f):
        split_list = f.__str__().split(';')
        self.selected_hierarchy_id = int(split_list[3])
        self.selected_tagset_id = int(split_list[4])
        photocube.ui.coremenu.context_menu_handler.open_context_hierarchy()

    
    def on_tagset_right_click(self, f):
        """
        Function for opening dimension context.       
        """
        split_list = f.__str__().split(';')
        self.selected_tagset_id = int( split_list[ len(split_list)-1 ] )
        
        t_id = photocube.objectcube.objectCubeService.get_tagset_by_id(self.selected_tagset_id).typeId
        print 't_id' + str(t_id)
        if t_id == photocube.objectcube.framework.TagSet.TYPE.ALPHANUMERICAL:
            print 'ALPHANUMERICAL'
            photocube.ui.coremenu.context_menu_handler.open_context_tagset_search_alphanumerical()
        elif t_id == photocube.objectcube.framework.TagSet.TYPE.RGB:
            print 'RGB'
            photocube.ui.coremenu.context_menu_handler.open_context_tagset_search_rgb()
        '''
        if t_id == photocube.objectcube.framework.TagSet.TYPE.ALPHANUMERICAL:
            photocube.ui.coremenu.context_menu_handler.open_context_tagset_alphanumerical()
        else:
            photocube.ui.coremenu.context_menu_handler.open_context_tagset_numerical()
        '''
    
    
    
    
    def hide(self):
        #self.right_menu_node_path.hide()
        
        if self.dimension_scrollbar is not None:
            self.dimension_scrollbar.hide()
        
        self.filter_menu.hide()
        
        # hide the background image
        self.bg.hide()
        self.is_visable = False

    
    
    
    
    def show(self):
        #self.right_menu_node_path.show()
        
        if self.dimension_scrollbar is not None:
            self.dimension_scrollbar.show()
        
        #self.filter_menu.show()
        
        # hide the background image
        #self.bg.show()
        self.is_visable = True

    

    def setXViewText(self, text):
        self.text_x.setText('front: ' + text)


    def setYViewText(self, text):
        self.text_y.setText('in: ' + text)

    def setZViewText(self, text):
        self.text_z.setText('up: ' + text)


    def __register_view_menu_messages(self):
        # Click messages for dimensions.        
        base.accept(self.curXDimRightClickMessage, self.on_x_view_right_click)
        base.accept(self.curXDimLeftClickMessage, self.on_x_view_right_click)
        base.accept(self.curYDimRightClickMessage, self.open_context_view_y)
        base.accept(self.curYDimLeftClickMessage, self.open_context_view_y)
        base.accept(self.curZDimRightClickMessage, self.open_context_view_z)
        base.accept(self.curZDimLeftClickMessage, self.open_context_view_z)
        base.accept('clear_glow', self.clear_glow)
        base.accept('zoomout_none', self.clear_glow) 


    def __placement(self, task):
        """
        Called to fix the size, location of object when the aspect changes.
        """
        if self.is_visable:            
            base.camLens.setAspectRatio(base.getAspectRatio())
            wp = base.win.getProperties()
            base.camLens.setAspectRatio((wp.getXSize()+0.0) / (wp.getYSize()+0.0))
            self.right_menu_node_path.show()
        
            self.right_menu_node_path.setX( (base.getAspectRatio()+(0.40/base.getAspectRatio())) )
            
            # Fix the position of the menu background image.
            self.bg.setX(0.32 + base.getAspectRatio())
            
            
            if self.dimension_scrollbar is not None:
                self.dimension_scrollbar.setX(base.getAspectRatio() - 0.04)
                self.dimension_scrollbar.setZ(0.18)
                
 
        else:
            # set the position for the dimensino buttons
            base.camLens.setAspectRatio(base.getAspectRatio())
            wp = base.win.getProperties()
            base.camLens.setAspectRatio((wp.getXSize()+0.0) / (wp.getYSize()+0.0)) 
            #self.right_menu_node_path.setX( (base.getAspectRatio()+(0.3/base.getAspectRatio())) ) 
            self.right_menu_node_path.hide()
            self.right_menu_node_path.setX(500)
            
            #THIS IS NOT ALLOWD, CLOSES CLUSTER MENUS AS WELL!
            #messenger.send('CLOSE_ALL_CONTEXT')
            
            # Fix the position of the menu background image.
            self.bg.setX(0.95 + base.getAspectRatio())
            self.bg.show()           
        
        
        
        return task.cont






class FilterMenu(AbstractMenu):
    def __init__(self, max_visiable_filter_cards=None, np=None, begin_pos = None):
        
        AbstractMenu.__init__(self)
        
        self.np = np
        
        # How many filters should we show in the filter list.
        self.max_filter_visable_in_menu = 8
        
        # Upper and lower bound for the menu. 
        self.filter_lower = 0
        self.filter_upper = self.max_filter_visable_in_menu
        
        # Member variable that keep that value of the scroll bar.
        self.scroll_value = 0
        self.filter_label_np = None
        
        # Keeps the position where the filter menu is placed.
        self.begin_pos = begin_pos
        
        # Member variable for the scrollbar.
        self.dimension_scrollbar = None
        
        # Variable that contains the current selected filter card.
        self.selected_filter_id = None
        
        # Task for keeping the location of objects in correct location with respect to screen aspect.
        #base.taskMgr.add(self.__placement, 'menuplacement_left_panel')
        
        base.accept('menu_update_filters', self.reload)


    def get_selected_dim_id(self):
        """
        Member function that returns the current selected
        filter id.
        """
        return self.selected_filter_id
    
    def __placement(self, task):
        """
        Called to fix the size, location of object when the aspect changes.
        """
        if self.dimension_scrollbar is not None:
            self.dimension_scrollbar.setX(base.getAspectRatio()-0.04)
            self.dimension_scrollbar.setZ(-0.57)
        return task.cont


    
    def move_filter_list_up(self):
        """
        Function for moving the filter list up.
        """
        if self.filter_lower > 0:
            self.filter_lower -= 1
            self.filter_upper -= 1 
            self.show_filter_cards()
            
    
    def move_filter_list_down(self):
        """
        Function for moving the list down.
        """
        if self.filter_upper < len( self.cards ):
            self.filter_lower += 1
            self.filter_upper += 1 
            self.show_filter_cards()
            
    
    def show_filter_cards(self):
        """
        Function for showing the cards.
        """
        for c in self.cards:
            c.hide()

        card_pos = self.begin_pos - 1.58
        for n in range(self.filter_lower, self.filter_upper):
            if n < len( self.cards ):
                self.cards[n].show()
                self.cards[n].setPos(-2.045, -1.3, card_pos)
                card_pos = card_pos - 0.053



    def on_card_click(self, np):
        # Save the filter id that is in scope.        
        a = np.__str__().split('/')
        for n,val in enumerate(a):
            print n, val
        
        filter_id = a[4].split('-')[1]
        print 'filter_id', filter_id
        self.selected_filter_id = int(filter_id)

        # Open up context menu for the filter.
        photocube.ui.coremenu.context_menu_handler.open_filter_context()




    def create_scrollbar( self ):      
        r = math.floor(len(self.cards) / self.max_filter_visable_in_menu)
        self.dimension_scrollbar = DirectScrollBar(range=(0, r), orientation= DGG.VERTICAL, command=self.on_dimension_scroll_change, scrollSize=1, pageSize=1, value=0)
        self.dimension_scrollbar.setScale(0.5, 1, 0.48)
        self.dimension_scrollbar['frameColor'] = (0.6,0.6,0.6,0.2)
        
        # disable the click sound for the scrollbar.
        self.dimension_scrollbar['incButton_rolloverSound'] = None
        self.dimension_scrollbar['decButton_rolloverSound'] = None
        self.dimension_scrollbar['thumb_clickSound'] = None
        self.dimension_scrollbar['thumb_rolloverSound'] = None
        self.dimension_scrollbar['incButton_relief'] = None
        self.dimension_scrollbar['decButton_relief'] = None
        self.dimension_scrollbar['decButton_text'] = '-'
        self.dimension_scrollbar['decButton_text_scale']=0.07
        self.dimension_scrollbar['incButton_text'] = '+'
        self.dimension_scrollbar['incButton_text_scale']=(0.07,0.05)
        self.dimension_scrollbar['incButton_text_pos'] = (-0.005,-0.02)
        self.dimension_scrollbar['decButton_text_pos'] = (-0.005,-0.02)
        self.dimension_scrollbar['thumb_frameColor'] = (0, 0, 0, 0.2)
        self.dimension_scrollbar.setX(base.getAspectRatio()-0.04)
        self.dimension_scrollbar.setZ(-0.50)    
    
    
    def on_dimension_scroll_change(self):
        
        val = int(self.dimension_scrollbar['value'])
        print 'val', val
        if val == self.scroll_value:
            print 'do nothing'
            return
        
        elif val < self.scroll_value:
            print 'scroll down'
            for n in range(self.scroll_value-val):
                self.move_filter_list_up()
        else:
            for n in range(val - self.scroll_value):
                self.move_filter_list_down()
                
        self.scroll_value = val
    

    
    
    def reload(self):        
        # Remove the old np for the filters and create new one.
        if self.filter_label_np is not None:
            self.filter_label_np.remove()
        self.filter_label_np = self.np.attachNewNode('filter-label-np')

        if self.dimension_scrollbar is not None:
            self.dimension_scrollbar.remove()
            self.dimension_scrollbar = None
        
        self.filter_scroll_value = 0

        # remove all the cards.
        self.remove_cards()
        print 'card contains', len(self.cards)

        
        # pos for the text label
        card_pos = self.begin_pos - 1.58

        for filter in photocube.objectcube.objectCubeService.get_filters():
            # we must check if this filter is in the cord node collection.
            # if it is, and is not the first one, then we don't add it.
            #found = False
            show = True

            if not show: continue            

            # Create new np
            dim_np = self.filter_label_np.attachNewNode('filter_np-' + str(filter.id))

            # Get the tagset that the filter is applying to.
            tagset = photocube.objectcube.objectCubeService.get_tagset_by_id(filter.tagSetId)

            # Create title for the card.
            if type(filter) == ObjectCubePython.TagFilter:
                tag = tagset.getTag(filter.tagId)
                title = 'Tag filter:' + ' ' + tagset.name + ' / ' + tag.valueAsString()
            
            elif type(filter) == ObjectCubePython.NumericalRangeFilter:
                title = 'Range filter: ' + tagset.name + " " + str(filter.numberFrom) + '-' + str(filter.numberTo) 

            elif type(filter) == ObjectCubePython.DimensionFilter:
                title = "Dimension filter: " + tagset.name 
            
            else:
                title = filter.typeAsString() + ' ' + tagset.name
            

            # Create new node path for the this filter card+label
            n = self.filter_label_np.attachNewNode( str(filter.id) )

            # Create a card to make the dimension clickable
            card_np = dim_np.attachNewNode('card-filter-'+ str(filter.id))
            card_np = card_np.attachNewNode('card-filter-np')
            card_np.setPos(1,1.5,1.5)
            cm = CardMaker('card')
            card = card_np.attachNewNode(cm.generate())
            card.setScale(0.50, 1, 0.050)                   
            card.setTwoSided(True)
            card.setColor(0,0,0)
            
            self.add_card(dim_np, card)

            # Create a new node for the text label.
            t_node = card.attachNewNode( 'card-label' + tagset.name )
            t_node.setY(-0.001)
            t_node.setZ(1.35)
            t_node.setX(0.03)

            t = OnscreenText(text=title, fg=(1,1,1,1), parent=t_node, pos=(0, -1, -4), scale=(0.075, 0.72), align=TextNode.ALeft)
            
            self.add_card_np( dim_np )

            # Set the position of the card.
            dim_np.hide()

            # update the next position.
            card_pos = card_pos - 0.053


        if len( self.cards ) > self.max_filter_visable_in_menu:
            self.create_scrollbar()

        self.show_filter_cards()


    def btn_filters(self, index):
        """
        This function is called when we select items from the context menu.
        """
        if index == 'remove filter':
            sid = self.get_selected_dim_id()
            sel_filter = photocube.objectcube.objectCubeService.get_filter_by_id( sid )
            ObjectCubePython.State.removeFilter(sel_filter)
            self.reload()
            photocube.cube.cubeService.reload()