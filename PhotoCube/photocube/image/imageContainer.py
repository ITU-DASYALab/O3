import threading
import time
import Queue
import PIL
from pandac.PandaModules import *
import PIL

active_queues = list()


class ImageContainer(threading.Thread):
    """
    Document string for ImageContainer  
    """
    
    def __init__(self):
        """
        Document string for constructor
        """
        self.max_size_mid = 500
        self.loadStack = list()
        self.images = dict()
        threading.Thread.__init__(self)
        self.pause = True
        
        self.mailbox = Queue.Queue()
        active_queues.append(self.mailbox)
        

    def contains(self, imageName):
        return imageName in self.images.keys()
    
    def getImage(self, imageName):
        return self.images[imageName]
    
    
    
    def run(self):
        """
        while True:
            data = self.mailbox.get()
            while True: pass
            
                
            if data not in self.images.keys():
                
                im = PIL.Image.open(data)
                xSize = im.size[0]
                ySize = im.size[1]
                image_ratio = (xSize / (ySize + 0.0))
                
                if image_ratio > 1:
                    width, height = (self.max_size_mid, self.max_size_mid / image_ratio)
                else:
                    width, height = (self.max_size_mid * image_ratio, self.max_size_mid)

                image = PNMImage()
                image.setReadSize(width, height)
                image.read(Filename(data))
                self.images[data] = image
                #print '--Image stored in container', data, len(self.images)
                #Thread.sleep(0.8)
        """
        pass
            
            
            
#######################################################################


