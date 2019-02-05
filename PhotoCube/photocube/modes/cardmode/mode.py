from photocube.modes import AbstractMode
from photocube.dialogs import TextDialog
from photocube.ui.coremenu import pluginButtonContainer
from photocube.objectcube import objectCubeService
from photocube.dialogs import dialogService
import photocube.modes
from handlers import CardNavigationHandler
from photocube.image import IMAGE_SIZE_MEDIUM, IMAGE_SIZE_SMALL



class CardMode( AbstractMode ):
    
    def __init__(self, name):
        AbstractMode.__init__(self, name)        
        self.image_click_messages = list()
    
    
    def disable(self):
        # Fix all the images that we were changing.
        selected_cluster = self.cube.getSelectedCells()
        for cell in selected_cluster:
            for image in cell.getVisableImages():
                image.reset_orientation()
                image.setDataSize( IMAGE_SIZE_SMALL)
                image.reload()
                image.scale_image()
                image.shake()
                image.hide_tags()
                #image.remove()

                # Clear the image click messages.
                for message in self.image_click_messages: 
                    base.ignore(message)
                    print 'REMOVE MESSAGE', message
                self.image_click_messages = list()
                
                
    def onImageClick(self, np, button):
        # Get the clicked object.
        object = objectCubeService.getObjectByName( str(np).split(';')[2] )
        
        # Open a dialog for adding to to the image.
        dialogService.openAddTagToObjectDialog(object)
        
        
    
    def initalize(self):
        print 'initalizing CardMode'
        # Add buttons to plugin button container.
        pluginButtonContainer.createButton("< Back", self.onBtnExitClick)
    
    
    def onBtnExitClick(self):
        print photocube.modes.modeService.enable_default_mode()
    
    
    def ShowloadingMessage(self):
        self.dlg = TextDialog(title="CardMode", message="Loading images, please wait..")
        self.dlg.draw()

    
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
        cis = CardNavigationHandler()
        
        # Move the image to another np.
        imgs = []
        
        for cell in selected_cluster:
            
            # Make all the images in the cluster visible.
            cell.makeAllImagesVisiable()
            for image in cell.getVisableImages():
                # remove the shake
                image.remove_shake()
                image.setDataSize( IMAGE_SIZE_MEDIUM )
                image.reload()
                imgs.append( image )
                
        imgs.sort(key=lambda x: x.location)


        # add the images to the ClusterImageService (change this name!!!!)
        cis.set_cluster_images( imgs )
        
        cis.set_first_image( cube.getLastClickedImage() )
        cis.start()
        
        # Get contect click event for images.
        for cell in selected_cluster:
            for image in cell.getVisableImages():
                #print image.get_click_message()
                #self.image_click_messages.append( image.get_click_message() )
                #base.accept(image.get_click_message(), self.onImageClick)
                pass # HERE WE NEED TO FIX CLICK STUFF

        # bind events for array left and array right
        base.accept( 'arrow_left', cis.view_left_cluster_image )
        base.accept( 'arrow_right', cis.view_right_cluster_image )

        # close the loading dialog
        self.dlg.Close()
 
