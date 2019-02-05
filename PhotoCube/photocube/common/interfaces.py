class Clickable:
    def __init__(self):
        #print 'Constructor for clickable class'
        pass
    
    def get_click_message(self):
        """
        Abstract function, derived classes must implement this.
        """
        raise NotImplementedError( 'Unimplamented function' )



class Hoverable:
    def __init__(self):
        #print 'Constructor for clickable class'
        pass

    def get_mouseover_message(self):
        """
        Abstract function, derived classes must implement this.
        """
        raise NotImplementedError( 'Unimplamented function.' )

    def get_mouseleave_message(self):
        """
        Abstract function, derived classes must implement this.
        """
        raise NotImplementedError( 'Unimplamented function' )
