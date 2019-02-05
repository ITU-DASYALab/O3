from abstract import AbstractAction
DEBUG = True

class ActionManager:
    """
    Action manager allows other code to add actions.
    """
    def __init__(self):
        """
        Constructor for the ActionManager class.
        """
        self.actions = []
    
    
    def addAction(self, action):
        """
        Adding new action to the action manager for loggin
        action history. Accepts action object.
        """
        if not isinstance(action, AbstractAction):
            raise ActionManagerException('addAction expects ' + type(AbstractAction).__str__() + " instance as parameter.")
        
        self.actions.append(action)
        
        if DEBUG: 
            print 'Added action to actionManager', action
            print 'Current action list:'
            for n,action in enumerate(self.getActions()):
                print n, action, action.getTimestamp()
            print ''
    
    
    def getActions(self):
        return self.actions
    
    
    def clearActions(self):
        """
        Cleares the actions from the current action list.
        """
        self.self.actions = []
