class AbstractMode:
    def __init__(self, mode_name):
        self.mode_name = mode_name
        self.enable_key = None

    def get_mode_name(self):
        return self.mode_name

    def get_enable_key(self):
        return self.enable_key
    
    def set_enable_key(self, key):
        self.enable_key = key
        base.accept( key, self.enable )

    def initalize(self):
        """
        This function is called when the model is first loaded. If the mode
        is loaded again, then this function is not called.
        """
        raise NotImplementedError( 'Unimplamented function initalize' )
    
    def enable(self):
        """
        This function is called to enable the mode.
        """
        messenger.send('change-mode', [self.mode_name])

    
    def disable(self):
        """
        This function is called when the model is disabled at the end.
        Do all de-initaliztion here.
        """
        raise NotImplementedError( 'Unimplamented function disable' )
    

    def load(self, coordinateService):
        raise NotImplementedError( 'Unimplamented function load' )


    def exit(self, go_to_mode=None):
        raise NotImplementedError( 'Unimplamented function exit' )
  
    
    def __str__(self):
        return self.mode_name




  
    













