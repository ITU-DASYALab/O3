from framework import objectCubeService

class FilterManger:    
    
    def __init__(self):
        """
        """
        self.__filters = []
        self.__stored_filters = []
    
    
    def add_filter(self, filter, store=False):
        """
        """
        print("add_filter")
        if store:
            self.__stored_filters.append( filter )
            
        else:
            self.__filters.append( filter )
            
        objectCubeService.get_state().addFilter( filter )
        objectCubeService.update_state()
    
    
    def add_filters(self, filters, store=False):
        """
        """
        print("add_filters")
        if store:
            for f in filters : 
                self.__stored_filters.append( f )
                objectCubeService.get_state().addFilter( f )
            
        else:
            for f in filters: 
                self.__filters.append( f )
                objectCubeService.get_state().addFilter( f )
                print '-- adding filter', f, f.id
            
        objectCubeService.update_state()
        print("add_filters finish") 


    def remove_filter(self, filter):
        objectCubeService.get_state().removeFilter(filter)
        self.__filters.remove( filter )
        print '-- removing filter', filter.id
        objectCubeService.update_state()


        
        
        
    def clear(self, remove_stored=False):
        """
        """
        for f in self.__filters:
            objectCubeService.get_state().removeFilter( f )
        
        self.__filters = []
        
        if remove_stored:
            for f in self.__stored_filters:
                objectCubeService.get_state().removeFilter( f )
            self.__stored_filters = []



# Create instance of the FilterManager.
filterManager = FilterManger()
        
    
    
    
        
