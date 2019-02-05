#imports
from abstract import AbstractAction

# ACTION TYPES
ACTION_ADD = 'ACTION_ADD'
ACTION_DELETE = 'ACTION_DELETE'
ACTION_MODIFY = 'ACTION_MODIFY'
ACTION_SET = 'ACTION_SET'
ACTION_CLEAR = 'CLEAR'
ACTION_SWAP = 'SWAP'
ACTION_MOVE = 'MOVE'
ACTION_DRILL_DOWN = 'DRILL_DOWN'
ACTION_DRILL_UP = 'DRILL_UP'

# Action names
ACTION_TAGSET = 'ACTION_TAGSET'
ACTION_HIERACHY = 'ACTION_HIERACHY'
ACTION_AXIS = 'ACTION_AXIS'
ACTION_TAGFILTER = 'ACTION_TAGFILTER'
ACTION_DIMENSIONFILTER = 'ACTION_DIMENSIONFILTER'
ACTION_TYPE_NUMERICAL_RANGEFILTER = 'ACTION_TYPE_NUMERICAL_RANGEFILTER'



class ActionAxis(AbstractAction):
    
    def __init__(self, actionType, axis1, axis2=None, tagId=None):
        AbstractAction.__init__(self, actionType, ACTION_AXIS)
        self.axis1 = axis1
        self.axis2 = axis2
        self.tagId = tagId
        print '-- Create actionAxis'
    
    
    def getAxis1(self):
        """docstring for getAxis1"""
        return self.axis1
    
    
    def getAxis2(self):
        return self.axis2
    
    
    def __str__(self):
        return self.getActionName() + ' ' + self.getActionType() + ' axis1:' + str(self.axis1) + ' axis2:' + str(self.axis2) + ' tagId:' + str(self.tagId)
        

#######################################################################
class ActionHierachy(AbstractAction):
    """docstring for ActionHierachy"""
    
    def __init__(self, actionType, tagsetId, dimensionId, axis):    
        AbstractAction.__init__(self, actionType, ACTION_HIERACHY)
        self.__tagsetId = tagsetId
        self.__dimensionId = dimensionId
        self.__axis = axis
        print 'Created action', 'action hierarchy'
    
    def getTagsetId(self):
        """ Getter function for Tagset id """
        return self.__tagsetId
    
    def getDimensionId(self):
        """ Getter function for dimension id """
        return self.__dimensionId
        
    def getAxis(self):
        """docstring for getAxis"""
        return self.__axis
    
    def __str__(self):
        """docstring for __str__"""
        return self.getActionName() + ' ' + self.getActionType() + ' on tagset ' + str(self.__tagsetId) + ' and dimension ' + str(self.__dimensionId) + " on axis " + str(self.getAxis())
        



class ActionTagset(AbstractAction):
    """docstring for ActionTagset"""    
    def __init__(self, actionType, tagsetId, axis):
        AbstractAction.__init__(self, actionType, ACTION_TAGSET)
        
        # Store the tagset id as member variable.
        self.tagsetId = tagsetId
        self.axis = axis
    
    def __str__(self):
        return self.getActionName() + ' ' + self.getActionType() + ' on tagset ' + str(self.tagsetId) + " axis " + str(self.getAxis())
    
    def getTagsetId(self):
        return self.tagsetId

    def getAxis(self):
        """docstring for getAxis"""
        return self.axis




class ActionFilter(AbstractAction):
    """docstring for ActionAddTagFilter"""
    
    def __init__(self, actionName, actionType, 
    tagsetId=None, tagId=None, dimensionId=None, hirarchyId=False, lowerValue=None, higherValue=None):        
        AbstractAction.__init__(self, actionType, actionName)
        self.__tagsetId = tagsetId
        self.__tagId = tagId
        self.hirarchyId = hirarchyId
        self.lowerValue = lowerValue
        self.higherValue = higherValue
    
    def getTagId(self):
        """docstring for getTagId"""
        return self.__tagId
    
    
    def getTagsetId(self):
        """docstring for getTagsetId"""
        return self.__tagsetId
    
    def __str__(self):
        """docstring for __str__"""
        return self.getActionName() + ' ' + self.getActionType() + " on tagset " + str(self.__tagsetId) + ' on tag ' + str(self.__tagId)
        
        #return actionType
        
        
        
