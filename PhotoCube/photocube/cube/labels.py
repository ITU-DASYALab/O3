from direct.gui.OnscreenText import OnscreenText
from pandac.PandaModules import CardMaker
from photocube.modes.mode import *
import photocube.cube
from pandac.PandaModules import TransparencyAttrib
from photocube.common import X_AXIS, Y_AXIS, Z_AXIS
from photocube.devices import mouse_handler
from photocube.ui.fonts import font

class AbstarctLabel:
    """
    AbstractLabel serves as a parent type for labels. This class contains
    everything that is common with coordinate labels.
    """
    
    def __init__(self, pos, tag, axis_num):
        """
        Constructor for the AbstractLabel class. Calculates the correct screen pos of
        the label with respet to axis number (x,y or z)
        """
        self.pos = pos
        self.screenPos = (0,0,0)
        self.tag = tag
        self.axis_num = axis_num
        
        self.__calculatePosition()
    
    
    def __calculatePosition(self):
        pos_x = 0
        pos_y = 0
        pos_z = 0
        
        #self.axis_num = axis_num 

        if self.axis_num is X_AXIS: 
            pos_x = (photocube.cube.cubeService.get_max_image_size()/2.0) + self.pos[0] * (photocube.cube.cubeService.get_max_image_size() + photocube.cube.cubeService.get_max_image_space())
            pos_y = 0
            pos_z = 0

        if self.axis_num is Y_AXIS:
            pos_x = 0
            pos_y = (photocube.cube.cubeService.get_max_image_size()/2) + self.pos[1] *(photocube.cube.cubeService.get_max_image_size() + photocube.cube.cubeService.get_max_image_space())
            pos_z = 0

        if self.axis_num is Z_AXIS:
            pos_x = -1
            pos_y = 0
            pos_z = (photocube.cube.cubeService.get_max_image_size()/2) + self.pos[2] *(photocube.cube.cubeService.get_max_image_size() + photocube.cube.cubeService.get_max_image_space())

        if pos_z == 0:
            pos_z = -1
        
        self.screenPos = (pos_x, pos_y, pos_z)
    
    
    def get_pos(self):
        """
        Getter function for the position of the label.
        """
        return self.pos
    
    def getScreenPos(self):
        return self.screenPos
    
    
    def update(self):
        self.__calculatePosition()
        self.np.setPos( self.screenPos )
###########################################################################################




class DrillUpLabel:
    def __init__(self, parent_np, node, axis):
        """
        Constructor for the DrillUpLabel. Creates nps for the object and sets
        the position of it.
        """
        self.axis = axis
        # Member variables for the constructor parameters.
        if self.axis == X_AXIS:
            self.parent_np = parent_np.attachNewNode('x_parent_node')
        
        elif self.axis == Y_AXIS:
            self.parent_np = parent_np.attachNewNode('y_parent_node')
        
        elif self.axis == Z_AXIS:
            self.parent_np = parent_np.attachNewNode('z_parent_node')
        else:
            raise Exception("Unknown axis.")


        self.node = node
        
        self.label_text = '-' + node.getNode().name
        self.np = self.parent_np.attachNewNode( self.label_text )
        self.text_np = self.np.attachNewNode('text-'+ self.label_text)
        self.card_np = self.np.attachNewNode('card-'+ self.label_text)
        
        if self.axis == Z_AXIS:
            self.np.setR(-90)
        

    def create_label(self):
        """
        Function for creating the text label under the image.
        """
        textObject = OnscreenText(text = self.label_text, scale = 1, font=font, fg=(1,1,1,1))
        textObject.reparentTo(self.text_np)
        
    
    def getNode(self):
        return self.node
    
    def set_pos(self, pos):
        self.np.setPos( pos )

    def create_clickable_box(self):
        """
        Creates clickable card around the text label, and returns the click event
        message used when the card is clicked.
        """
        # Get the label text length.
        text_length = len(self.label_text)
        cm = CardMaker( 'card-'+self.label_text )
        card = self.card_np.attachNewNode(cm.generate())
        tex = loader.loadTexture('static/images/menu_left3.tif')
        
        card.setTexture(tex)
        card.setTransparency(TransparencyAttrib.MAlpha)
        #card.setScale(1.2*len(self.label_text),1,1)
        #card.setPos((-0.14*len(self.label_text)), 0.01, -0.3)

        card.setScale(0.5 * text_length,1,1)
        card.setPos((-0.25 * text_length, 0.01, -0.3))



        card.setTwoSided(True)
        
        # make the card pickable
        message = mouse_handler.makeNPPickableLeft(self.np)
        return message

    
    def update_pos(self):
        if self.axis == X_AXIS:
            num_labels = photocube.cube.cubeService.coordinate.x.get_node_count() # this only works for X
            img_size = photocube.cube.cubeService.get_max_image_size()
            img_space = photocube.cube.cubeService.get_max_image_space()
            x_pos = (num_labels * img_size) + ((num_labels-1) * img_space)
            self.set_pos( (x_pos/2.0, 0, -3) )
        
        elif self.axis == Y_AXIS:
            num_labels = photocube.cube.cubeService.coordinate.y.get_node_count()
            img_size = photocube.cube.cubeService.get_max_image_size()
            img_space = photocube.cube.cubeService.get_max_image_space()
            y_pos = (num_labels * img_size) + ((num_labels-1) * img_space)
            self.set_pos( (0, (y_pos)/2.0, -3) )


        elif self.axis == Z_AXIS:
            num_labels = photocube.cube.cubeService.coordinate.z.get_node_count()
            img_size = photocube.cube.cubeService.get_max_image_size()
            img_space = photocube.cube.cubeService.get_max_image_space()
            z_pos = (num_labels * img_size) + ((num_labels-1) * img_space)
            self.set_pos( (-3, 0, z_pos/2.0) )


        else:
            raise Exception('Unabel to handle position request, unknown axis.')


    def remove(self):
        """
        Function for removing current label.
        """
        self.parent_np.remove()






class AxisLabel(AbstarctLabel):
    """
    This class represents label on the coordinate.
    """
    def __init__(self, title, pos, tag, axis_num):
        AbstarctLabel.__init__(self, pos, tag, axis_num) 
        self.title = title
        self.np = None
        self.hierarchy = False
        self.click_event_name = None
        self.simple_cord = 0
        self.picker_message = None
        self.aggrigation_num = None
        self.axisLabelTextLength = 0
    
    def __str__(self):
        return self.title

    def __unicode__(self):
        return self.title
    
    
    
    def updatePosHpr(self):
        self.np.setHpr(-base.camera.getHpr())
    
    
    
    
    def set_parent(self, parent):
        self.parent = parent

    
    def set_hierarchy(self, value):
        self.hierarchy = value

    def get_hierarchy(self):
        return self.hierarchy 

    
    def get_picker_message(self):
        return self.picker_message

    
    def set_aggrigation_num(self, num):
        self.aggrigation_num = num

    
    def get_aggrigation_num(self):
        return self.aggrigation_num
   

    #TODO: What is going on here?
    def change(self):
        
        # Get the current mode.
        curr_mode = photocube.modes.modeService.get_mode()
        
        if curr_mode == SCATTERING_VIEW_MODE:
            cord_serv = photocube.cube.cubeService
            root = cord_serv.get_coordinate().root_np
            self.np.setP( -1 * root.getP() )
        
        else:
            self.np.setH(base.camera.getH())
            self.np.setR(base.camera.getR())
            self.np.setP(base.camera.getP())
    
    
    
    def hide(self):
        self.np.hide()
    
    
    def create_click_card(self):
        # Creade card behind the label. Used for enable mouse click on the label.                    
        if self.hierarchy:
            cm = CardMaker('card-'+self.title)
            card = self.card_np.attachNewNode(cm.generate())
            tex = loader.loadTexture('static/images/menu_left3.tif')
            card.setTexture(tex)
            card.setTransparency(TransparencyAttrib.MAlpha)
            card.setScale(0.5 * self.axisLabelTextLength,1,1)
            card.setPos((-0.25 * self.axisLabelTextLength), 0.01, -0.3)
            card.setTwoSided(True)
        
    
    
    def create(self):
        self.click_event_name = self.title
        
        # Create node paths for the label.
        self.np = self.parent.attachNewNode(self.click_event_name)
        self.text_np = self.np.attachNewNode('text-'+ self.title)
        self.card_np = self.np.attachNewNode('card-'+ self.title)
        
        
        # Create the text object.
        # read the font from configuration.
        textObject = None
        # If we have a hierachy we pad + sign in front of the name. Good idea to place some
        # good image indicator that this label is clickable.
        
        text_color =(0,0,0,1) #text color
        if self.hierarchy:
            label_text = '+' + self.title
            if self.aggrigation_num is not None:
                label_text += ' (' + str( self.aggrigation_num ) + ')'
                # fix for the size of the clickable card.
                self.axisLabelTextLength = len(label_text)
            textObject = OnscreenText(text = label_text, scale = 1, fg=text_color, font=font)
        else:
            textObject = OnscreenText(text = self.title, scale = 1, fg=text_color, font=font)
        
        textObject.reparentTo(self.text_np)
        textObject.setTwoSided(True)

        # If this is a hierarchy label, we make it clickable. 
        if self.hierarchy:
            self.picker_message = mouse_handler.makeNPPickableLeft(self.np)

        
        # Set the position of the label.        
        self.np.setPos(self.pos[0], self.pos[1], self.pos[2])
        
        # if this is z 
        if self.axis_num == 2:
            self.np.setR(-90)
            self.np.setX(-1)
        #print self.axis_num

