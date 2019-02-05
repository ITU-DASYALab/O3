from datetime import datetime


class AbstractAction: 
    """
    Abstract class for actions. Provides basic functionality
    for for deriving actions.
    
    """
    def __init__(self, actionType, actionName):
        """
        Constructor for the AbstractAction.
        """
        self.__actionType = actionType
        self.__actionName = actionName
        # Create a time stamp for this action.
        self.__timeStamp = datetime.now()
    
    def getActionType(self):
        """
        Returns the type of the action. The type returned
        is the type of the derriving class.
        """
        return self.__actionType
    
    
    def getActionName(self):
        """
        Returns the action name.
        """
        return self.__actionName
            
            
    def getTimestamp(self):
        """
        Returns the time stamp for a given action.
        """
        return self.__timeStamp
