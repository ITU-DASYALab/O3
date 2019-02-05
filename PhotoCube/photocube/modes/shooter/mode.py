from photocube.modes import AbstractMode
from photocube.dialogs import TextDialog
from photocube.ui.coremenu import pluginButtonContainer
#from browser.objectcube import objectCubeService
#from browser.dialogs import dialogService
import photocube.modes
#from handlers import CardNavigationHandler
from photocube.image import IMAGE_SIZE_MEDIUM, IMAGE_SIZE_SMALL
import random
from direct.interval.IntervalGlobal import *



class ShooterMode( AbstractMode ):
    
    def __init__(self, name):
        AbstractMode.__init__(self, name)        
        self.image_click_messages = list()
        
        self.imageNP = render.attachNewNode( 'Shooter image np' )
    
    
    def disable(self):
        
        # stop all lerps
        for x in self.imgs.values():
            x[1].finish()
        
        
        # Fix all the images that we were changing.
        selected_cluster = self.cube.getSelectedCells()
        for cell in selected_cluster:
            for image in cell.getVisableImages():
                image.reset_orientation()
                image.setDataSize( IMAGE_SIZE_SMALL)
                image.reload()
                image.scale_image()
                image.shake()

                # Clear the image click messages.
                for message in self.image_click_messages: 
                    base.ignore(message)
                    #print 'REMOVE MESSAGE', message
                self.image_click_messages = list()
                
                
    def onImageClick(self, np):

        inkey = int(str(np).split(';')[1])
        image = self.imgs[inkey][0]
        image_lerp = self.imgs[inkey][1]
        image_range = self.imgs[inkey][2]
        
        if(image_range):
            pos = image.get_np().getPos()
            image_lerp.finish()
            image.get_np().setPos(pos)
            LerpHprInterval(image.get_np(), 1, (random.randint(-360,360),random.randint(-360,360),random.randint(-360,360)), image.get_np().getHpr()).start()
            
            l = LerpPosInterval(image.get_np(),
                duration=1.5,
                pos=(10, 7000, 0), 
                startPos=image.get_np().getPos(),
                blendType='noBlend',
                bakeInStart=1,
                fluid=0).start()
        
            
              
        
        
        #(image, l , False)

        
        
    
    def initalize(self):
        print 'initalizing shooter'
        # Add buttons to plugin button container.
        pluginButtonContainer.createButton("< quit game", self.onBtnExitClick)
    
    
    def onBtnExitClick(self):
        print photocube.modes.modeService.enable_default_mode()
    
    
    def ShowloadingMessage(self):
        self.dlg = TextDialog(title="CardMode", message="Loading images for shooter game..")
        self.dlg.draw()

    
    def func(self, task):
        if task.time > 25:
            return task.done
        else:
            for key in self.imgs.keys():
                x = self.imgs[key]
                if x[2] == False:
                    self.imgs[key] = (x[0], x[1], True)
                    #print 'flip'
                    LerpHprInterval(x[0].get_np(), 0.8, (0,0,0), x[0].get_np().getHpr()).start()
                    return task.again
            
            
    
    
    
    
    def load(self, cube):
        
        # Show loading dialog.
        self.ShowloadingMessage() 
        
        # Force repaint for showing the dialog before the images.
        base.graphicsEngine.renderFrame()
        base.graphicsEngine.renderFrame()

        # Get the selected cells.
        self.cube = cube
        selected_cluster = cube.getSelectedCells()
        
        #print 'Cardmode got number of selected cluster', len(selected_cluster)
        
        # Create new ClusterImageService
        #cis = CardNavigationHandler()
        
        
        self.imgs = dict()
        
        for cell in selected_cluster:
            
            # Make all the images in the cluster visible.
            cell.makeAllImagesVisiable()
            for image in cell.getVisableImages():
                # remove the shake
                image.remove_shake()
                image.setDataSize( IMAGE_SIZE_MEDIUM )
                image.reload()
                image.scale_image()
                image.get_np().reparentTo(self.imageNP)
                image.get_np().setX(random.randint(-10,10))
                image.get_np().setY(random.randint(150,450))
                image.get_np().setZ(-5)
                
                # pitch the images
                image.get_np().setP(-90)
                base.camera.setPos(5,0,0)
                print str(image.get_np())
                
                
                base.accept('CLICK_MOUSE1_' + str(image.get_np()), self.onImageClick)


                
                
                # start a lerp for the image
                l = LerpPosInterval(image.get_np(),
                    duration=45,
                    pos=(image.get_np().getX(),40,image.get_np().getZ()), 
                    startPos=image.get_np().getPos(),
                    blendType='noBlend',
                    bakeInStart=1,
                    fluid=0)
                l.start()
                
                
                
                
                self.imgs[image.get_id()] = (image, l , False)
                
                
                #base.oobe()
                                
        

        
        # start game loop.
    
        taskMgr.doMethodLater( 1, self.func, 'tickTask')
        # close the loading dialog
        self.dlg.Close()

