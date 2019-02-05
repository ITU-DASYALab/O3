
import photocube.common
import sys

sys.path.append( '../ObjectCube' )
import ObjectCubePython

from photocube.objectcube import objectCubeService, filterManager
from photocube.image.img import *



class AbstractAxis:
    def __init__(self, is_hierarchy):
        self.__is_hierarchy = is_hierarchy
        self.axisColor = None
        
        # Member variable for axis index in ObjectCube.
        self.axis_index = None

    def set_axis_color(self, c):
        self.axisColor = c

    def get_axis_color(self):
        return self.axisColor
    
    def get_load_filter(self):
        raise NotImplementedError( 'Unimplamented function' )

    def is_hierarchy(self):
        return self.__is_hierarchy 

    def set_axis_index(self, index):
        self.axis_index = index

    def get_axis_index(self):
        return self.axis_index
    
    def get_node_count(self):
        raise NotImplementedError( 'Unimplamented function' )






class AxisHierarchy(AbstractAxis):
    def __init__(self, dim, curr_node=None, axis=None):
        """ Axis that can hold hirarchies. """
        
        if axis is None:
            raise Exception('Axis is missing for axis.')
        
        # Call the derrived class constructor
        AbstractAxis.__init__(self, is_hierarchy=True)
        
        # Member variable for the dim.
        self.tagset = dim
        self.dim = dim

        # Member variable for the load filter.
        self.load_filter = ObjectCubePython.DimensionFilter(self.tagset.getRoot(), self.tagset.tagSetId)

        # Member variable for branches
        self.current_nodes = []
        
        # Member variable for the root node.
        self.curr_node = curr_node
        
        # Member variable for hierarchy level.
        self.hirachyLevel = 0
        
        # reference to the cube...
        
        # Vorum ad adda thessum dudda inn.
        self.axis = axis


    def getLevel(self):
        """docstring for getLevel"""
        return self.hirachyLevel
    
    
    def setLevel(self, level):
        """docstring for setLevel"""
        self.hirachyLevel = level
    
    
    def get_load_filter(self):
       """docstring for getLoadfilter"""
       return self.load_filter
    
    
    def get_state_hierarchy_node(self):
        if self.curr_node is None:
            self.current_nodes = list()
            state_hir = objectCubeService.get_state().getDimension( self.tagset.id )
            
            print 'STATE', state_hir
            print dir(state_hir)
            
            
            children = state_hir.getRoot().getBranches()
            
            for child in children:
                self.current_nodes.append( child )
                objectCubeService.get_state()
            return state_hir.getRoot()
        
        else:
            # clear current_node array
            self.current_nodes = list()
            for b in self.curr_node.getBranches():
                self.current_nodes.append( b )
            return self.curr_node

    
   
    def get_node_by_label(self, label):
        n = self.dim.getNode(label)
        state_hir = objectCubeService.get_state().getDimension( self.tagset.id )
        node = state_hir.getNode( n.id )
        return node
    
    
    def get_node_by_label2(self, label):
        for node in self.current_nodes:
            print dir(node.getNode())
            if node.getNode().name == label:
                return node
        
        raise Exception('NOT WORKING')
    
    

    def drill_down(self, stateNode):
        """
        Document for drill_down
        """
        self.__init__(self.tagset, curr_node=stateNode, axis=self.axis)

    
    def drill_up(self, stateNode):
        """
        Document for drill_up
        """
        self.__init__(self.tagset, curr_node = stateNode, axis = self.axis)

    
    def get_node_count(self):
        return len(photocube.cube.cubeService.coordinate.cube.getLabelsForAxis(self.axis))

    
    def get_parent_node_for_current(self):
        return objectCubeService.get_state().getDimension( self.tagset.id ).getParentNode( self.curr_node.getNode().id )

    
    def get_parent_for_node(self, node):
        parent = objectCubeService.get_state().getDimension( self.tagset.id ).getParentNode( node.getNode().id )
        return parent
    
    def get_current_node(self):
        return self.curr_node








class AxisTagset(AbstractAxis):
    def __init__(self, tagset, axis):
        
        if axis is None:
            raise Exception('Axis is missing for axis.')
        
        # Call the derrived class constructor
        AbstractAxis.__init__(self, False)
        
        # Reference to the tagset that is on this axis.
        self.tagset = tagset
        
        self.axis = axis
        
        # Reference to the tagset.
        self.tagset = tagset
        
        # Reference to the default dimension for this tagset.
        self.default_dim = self.tagset.getDefaultDimension()

        # The load filter used for this tagset.
        self.load_filter = ObjectCubePython.DimensionFilter(self.default_dim.getRoot(), self.tagset.id)

    
    def get_load_filter(self):
        return self.load_filter
    
    
    def get_node_count(self):
        return len(photocube.cube.cubeService.coordinate.cube.getLabelsForAxis(self.axis))
