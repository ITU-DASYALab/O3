from direct.interval.LerpInterval import *
from photocube.dialogs import TextDialog
from direct.task import Task



class CardNavigationHandler:
    """
    CardNavigationHandler hanldes the card movements in the CardMode.
    """
    def __init__(self):
        self.images = None
        self.index = None
        self.speed = 0.4
        
        # Dict for the image positions in the clusters.
        self.image_cluster_pos = dict()
        
        
    def set_cluster_images(self, images):
        self.images = images
        print 'ClusterImage service contains', len(self.images), 'images.'
        
        
    def set_first_image(self, first):
        for i,image in enumerate(self.images):
            if image == first:
                self.index = i
                break
        if self.index == None:
            self.index = len(self.images) / 2
            
    def get_first(self):
        print self.index
        return self.images[self.index]
    
    
    def start(self):
        self.show_image_front(self.get_first())
        i = self.index - 1
        pos = 0
        
        while i >= 0:
            self.show_image_in_left_dock(self.images[i], pos)
            pos += 1
            i -= 1 
        
        num = 0
        
        for r in range(self.index+1, len(self.images)):
            self.show_image_in_right_dock(self.images[r], num)
            num += 1 
    
    
    
    def view_left_cluster_image(self):
        if self.index == 0:
            return
        
        # Move the images on the left side forward.
        i = self.index-1
        pos = 0
        while i >= 0:
            self.slide_left_image_forward(self.images[i])
            i -= 1
        
        # Move the images on the right side side backward.
        for r in range(self.index+1, len(self.images)):
            self.slide_right_image_in(self.images[r])   
        
        #self.images[self.index].scale_image(1)
        LerpFunc(self.imageScaleFunction, fromData = 1.5, toData = 1, duration = self.speed, blendType = 'noBlend', extraArgs = [self.images[self.index]], name = None).start()
        self.slide_right_image_in(self.images[self.index])
        
        
        #self.images[self.index].hide_tags()
        self.index -= 1
        self.slide_to_front(self.images[ self.index ])

        
    
    
    def view_right_cluster_image(self):
        if self.index == len(self.images)-1:
            #print 'cannot go more right'
            return
        
        # Move the images on the left side in.
        i = self.index-1
        pos = 0
        while i >= 0:
            self.slide_left_image_in(self.images[i])
            #self.images[i].slide_left_image_in()
            i -= 1
        
        self.image_cluster_pos[ self.images[self.index].id ] = -1
        
        
        
        #self.images[self.index].id = -1 #np.hide()
        #self.images[self.index].scale_image(1)
        LerpFunc(self.imageScaleFunction, fromData = 1.5, toData = 1, duration = self.speed, blendType = 'noBlend', extraArgs = [self.images[self.index]], name = None).start()



        self.slide_left_image_in( self.images[self.index] )
        #self.images[self.index].hide_tags()
        self.index += 1
        
        self.slide_to_front(self.images[ self.index ])
        
        for r in range(self.index+1,len(self.images)):
            self.slide_right_image_forward( self.images[r] )
            #self.images[r].slide_right_image_forward()


    
    
    def show_image_front(self, image):
        #print 'SHOW IMAGE FRONT!!!!'
        self.image_cluster_pos[ image.id ] = 0
        image.get_np().reparentTo(base.camera)
        image.get_np().setX(-0.8)
        image.get_np().setY(4)
        image.get_np().setZ(-0.7)
        image.get_np().setR(0)
        image.get_np().setH(0)
        image.scale_image(1.5, scale_tags=True)
        #image.get_np().show_tags()
        image.show_tags()
    
    
    def show_image_in_left_dock(self, image, num):
        #image.cluster_pos = num
        self.image_cluster_pos[ image.id ] = num
        #self.np.clearTexture()
        #self.scale = browser.image.img_service.get_max_picture_size()
        #self.scale_image_warg(1)
        image.scale_image(1, scale_tags=True)
        image.get_np().reparentTo(base.camera)
        image.get_np().setX(-1 - (num*0.15))
        image.get_np().setY(3.7 + (num*0.3))
        image.get_np().setZ(-0.7)
        image.get_np().setR(0)
        image.get_np().setH(60 + (num*0.1))


    def show_image_in_right_dock(self, image, num):
        #image.cluster_pos = num
        self.image_cluster_pos[ image.id ] = num
        #self.np.clearTexture()
        #self.scale = browser.image.img_service.get_max_picture_size()
        image.scale_image(1, scale_tags=True)
        image.get_np().reparentTo(base.camera)
        image.get_np().setX(0.5 + (num*0.15))
        image.get_np().setY(5 + (num*0.3))
        image.get_np().setZ(-0.7)
        image.get_np().setR(0)
        image.get_np().setH(-60 - (num*0.1))



    def slide_left_image_forward(self, image):
        #image.cluster_pos -=1
        #self.image_cluster_pos[ image.id ] -=1
        self.image_cluster_pos[ image.id ] -= 1
        #print 'sliding right', self.location, 'to', self.cluster_pos
        x = (-1 - (self.image_cluster_pos[ image.id ] * 0.15))
        y = (3.7 + (self.image_cluster_pos[ image.id ] * 0.3))
        z = (-0.7)
        h = (60 + (self.image_cluster_pos[ image.id ] * 0.1))
        LerpHprInterval(image.get_np(), 0.3, (h, image.get_np().getP(), image.get_np().getR()), image.get_np().getHpr()).start()
        LerpPosInterval(image.get_np(), 0.3, (x,y,z), image.get_np().getPos() ).start()
        #image.hide_tags()



    def slide_left_image_in(self, image):
        #image.cluster_pos +=1
        #self.image_cluster_pos[ image.id ] += 1
        self.image_cluster_pos[image.id] += 1
        #print 'sliding right', self.location, 'to', self.cluster_pos
        x = (-1 - (self.image_cluster_pos[ image.id ] * 0.15))
        y = (3.7 + (self.image_cluster_pos[ image.id ] * 0.3))
        z = (-0.7)
        h = (60 + (self.image_cluster_pos[ image.id ] * 0.1))
        
        #LerpFunc(self.imageScaleFunction, fromData = 1.5, toData = 1, duration = self.speed, blendType = 'noBlend', extraArgs = [image], name = None).start()
        
        LerpHprInterval(image.get_np(), self.speed, (h, image.get_np().getP(), image.get_np().getR()), image.get_np().getHpr()).start()
        LerpPosInterval(image.get_np(), self.speed, (x,y,z), image.get_np().getPos() ).start()
        image.hide_tags()



    def slide_right_image_in(self, image):
        #image.cluster_pos +=1
        #self.image_cluster_pos[ image.id ] += 1
        self.image_cluster_pos[image.id] += 1
        #self.np.hide()
        x = (0.5 + (self.image_cluster_pos[ image.id ] * 0.15))
        y = (5 + (self.image_cluster_pos[ image.id ] * 0.3))
        z = (-0.7)
        #self.np.setR(0)
        h = (-60 - (self.image_cluster_pos[ image.id ] * 0.1))
        LerpHprInterval(image.get_np(), self.speed, (h, image.get_np().getP(), image.get_np().getR()), image.get_np().getHpr()).start()
        LerpPosInterval(image.get_np(), self.speed, (x,y,z), image.get_np().getPos() ).start()
        image.hide_tags()


    
    def slide_right_image_forward(self, image):
        #image.cluster_pos -=1
        #self.image_cluster_pos[ image.id ] -= 1
        self.image_cluster_pos[image.id] -= 1
        x = (0.5 + (self.image_cluster_pos[ image.id ] * 0.15))
        y = (5 + (self.image_cluster_pos[ image.id ] * 0.3))
        z = (-0.7)
        h = (-60 - (self.image_cluster_pos[ image.id ] * 0.1))
        
        LerpHprInterval(image.get_np(), self.speed, (h, image.get_np().getP(), image.get_np().getR()), image.get_np().getHpr()).start()
        LerpPosInterval(image.get_np(), self.speed, (x,y,z), image.get_np().getPos() ).start()


    
    def slide_to_front(self, image):
        #print 'HERE!'
        #print image.width
        
        speed = 0.3
        
        LerpFunc(self.imageScaleFunction, fromData = 1, toData = 1.5, duration = speed, blendType = 'noBlend', extraArgs = [image], name = None).start()
     
        
        
        #image.get_np().setR(70)
        LerpHprInterval(image.get_np(), self.speed, (0,0,0), image.get_np().getHpr()).start()
        
        # Lerp the position
        #if image.width < 1:
        #    x_pos = image.width
        #else:
        x_pos = 0.3
        #LerpPosInterval( image.get_np(), x_pos, (-0.8, 4,-0.7), image.get_np().getPos() ).start()
        
        if image.width < 1:
            image_x_pos = -1 + 0.5#(image.width)
            #print image.width
        else:
            image_x_pos = -0.8
            
        LerpPosInterval( image.get_np(), self.speed, (image_x_pos, 4,-0.7), image.get_np().getPos() ).start()
        
        
        #image.scale_image(1.5)
        self.image_cluster_pos[image.id] = 0
        image.show_tags()



    #bad function, need to fix.
    def imageScaleFunction(self, t, image):
        image.scale_image(t, scale_tags=True)


