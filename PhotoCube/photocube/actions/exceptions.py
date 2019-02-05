class ActionManagerException(Exception):
    """
    User defined expection for ActionManager.
    """
    def __init__(self,  value):
        self.value = value
    
    def __str__(self):
        return repr(self.value)
