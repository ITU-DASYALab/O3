import random
from pandac.PandaModules import *
import PIL
import PIL.Image
import img

#############################################################
class ImageFactory:
    """
    Factory class for creating instances of Image objects.
    Handles unique id's for images.
    """
    def __init__(self):
        print '[' + str(self.__class__) + ']', 'Instance created'
        self.id_counter = 0
        self.images_np = None
    
    def set_images_np(self, np):
        self.images_np = np
    

    def get_image(self, location):
        # Create image object from the location.
        image = img.Image( self.id_counter, location )
        self.id_counter += 1
                
        # Set the image shake value.
        image.random_r = float(random.uniform(-4, 4))
        
        return image


# Create singleton instance.
image_factory = ImageFactory()
#############################################################



#############################################################
class ImageEventMessageService:
    """
    What is this?
    """
    def __init__(self):
        """
        Default constructor for the ImageEventMessageService.
        """
        print '[' + str(self.__class__) + ']: instance created.'
        self.messages = dict()
    
    def add_message(self, message, event_function):
        #self.__output_screen_message('added message ' + message)
        self.messages[ message ] = None
        base.accept( message, event_function )
    
    def contains_message(self, message):
        return message in self.messages.keys()
    
    def clear_messages(self):
        for message in self.messages.keys():
            base.ignore( message )
            self.__output_screen_message('removing message: ' + message)
        
        self.messages = dict()
        self.__output_screen_message('all messages cleared.')
    
    def __output_screen_message(self, message):
        print '[' + str(self.__class__) + ']:', message

image_event_service = ImageEventMessageService()
#############################################################
    
    



