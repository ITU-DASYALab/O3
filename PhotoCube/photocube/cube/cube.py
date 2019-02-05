#from browser.image import Image
from photocube.image.services import image_factory
from labels import AxisLabel
from collections import OrderedDict

###########################################################################
class Cell:
    """ Document string for Cell """
    def __init__(self, key):
        
        # Member variable for key.
        self.key = key
        
        # Member variables for the tags.
        self.x_tag = None
        self.y_tag = None
        self.z_tag = None
        
        # Member variable for the objects thta are in a given cell.
        self.images = OrderedDict()
        
    
    def getXtag(self):
        """ Getter function for x-tag  """
        return self.x_tag
    
    def getYtag(self):
        """ Getter function for y-tag  """
        return self.y_tag
    
    def getZtag(self):
        """ Getter function for z-tag  """
        return self.z_tag
    
    def setXtag(self, t):
        """ Setter function for x-tag  """        
        #print 'setting tag t', t
        self.x_tag = t

    def setYtag(self, t):
        """ Setter function for Y-tag  """    
        self.y_tag = t

    def setZtag(self, t):
        """ Setter function for z-tag  """    
        self.z_tag = t
    
    def addImage(self, image):
        """ Function for adding image to the cell  """            
        self.images[ image.get_location() ] = image
    
    def getKey(self):
        """ Function for getting the cell key """    
        return self.key
        
    def getImages(self):
        """ Function for getting all the images that
        the cell contains.
        """
        return self.images.values()
    
    def getVisableImages(self):
        imgs = []
        for image in self.images.values():
            if image.isVisible(): 
                imgs.append(image)
        return imgs


    def getNumberOfVisibleImages(self):
        return len(self.getVisableImages())


    def makeAllImagesHidden(self):
        for image in self.images.values():
            if not image.isVisible(): 
                image.hide()


    def makeAllImagesVisiable(self):
        for image in self.images.values():
            if not image.isVisible(): 
                image.show()
###########################################################################





###########################################################################
class Cube:
    
    def __init__(self, mdv, x, y, z, last_visible_images_dict = None):
        """ Cube is a wrapper around ObjectCubes MDV."""
        
        #print dir(mdv)
        
        
        if last_visible_images_dict is None:
            last_visible_images_dict = dict()
        
        # Member variables for axis.
        self.x = x
        self.y = y
        self.z = z
        
        # Create instance of the cubes cell dictionary.
        self.cells = dict()
       
        # Member variable for selected clusters.
        self.selected_clusters = list()

        # Member variables for image click and hover.
        self.last_clicked_image = None
        self.currentHoveredImage = None

        try:
            self.x_cell_count = mdv.getAxisCellCount( self.x.get_axis_index() )
            print '[Cube] x axis cell count is', self.x_cell_count
        except:
            self.x_cell_count = 0

        try:
            self.y_cell_count = mdv.getAxisCellCount( self.y.get_axis_index() )
        except:
            self.y_cell_count = 0
 
        try:
            self.z_cell_count = mdv.getAxisCellCount( self.z.get_axis_index() )
        except:
            self.z_cell_count = 0
 
        # Get the cells from ObjectCube mdv.
        cells = mdv.getCells(99999,99999)
        
        

       
        # Create the cell and set the axis label for it.
        for k in cells.keys():
            self.cells[ k ] = Cell( k )

            if x is not None:
                self.cells[k].setXtag( cells[ k ].getAxisLabel( self.x.get_axis_index() ) )

            if y is not None:
                self.cells[k].setYtag( cells[ k ].getAxisLabel( self.y.get_axis_index() ) )
            
            if z is not None:
                self.cells[k].setZtag( cells[ k ].getAxisLabel( self.z.get_axis_index() ) )
           
           
        # Keep the number of the dimensions in memory.
        self.num_dims = mdv.getNumberOfDimensions()

        
        for k in cells.keys():
            splt = k.split( ':' )

            xv = None
            zv = None
            yv = None
            
            if x is not None:
                xv = int(splt.pop(0))

            if y is not None:
                yv = int(splt.pop(0))

            if z is not None:
                zv = int(splt.pop(0))

            # Create position from mdv cell key.
            pos = (xv,yv,zv)

            # Temporary sorting of images in cell
            currentObjects = list(cells[k].getObjects())
            currentObjects.sort(key=lambda x: x.name)

            # Add the images in the mdv cell to our new cell with position set.

            for i,obj in enumerate( currentObjects ):                
                
                # Check if this image was in the last cube, if so we can reuse it.
                if obj.name.__str__() in last_visible_images_dict.keys():
                    if len( last_visible_images_dict[ obj.name.__str__() ] ) > 0:
                        old_image = last_visible_images_dict[obj.name.__str__()].pop()
                        print 'cube: reusing image with id', old_image.get_id(), old_image.isVisible()
                        old_image.set_pos( pos )
                        old_image.cluster_index = None
                        old_image.scale_image()
                        old_image.get_np().detachNode()
                        self.cells[k].addImage( old_image )
                        continue
                
                # If we did not reuse image, then we'll create new image object.
                image = image_factory.get_image( obj.name )
                image.set_pos( pos )
                image.cluster_index = None
                image.get_np().detachNode()
                self.cells[k].addImage( image )
            
        
        
        
        #The images that were not reused in the last visiable set
        # must be removed.
        for l in last_visible_images_dict.values():
            for image in l:
                image.get_np().detachNode()
                image.remove()
                #print 'REMOVING IMAGE, NOT IN THE CUBE', image.get_location()
        last_visible_images_dict = dict()


    
    
    def getLabelsForAxis(self, num):
        return_list = []
        
        if num == 2:
            for z in range(0, self.z_cell_count):
                k = ''
                
                if self.x is not None:
                    k = '0:'

                if self.y is not None:
                    k = k + '0:'

                k = k + str(z)
                cell = self.cells[k]
                
                tag = cell.getZtag()
                l = AxisLabel(tag, (0,0,z), tag, 2)
                
                if self.z.is_hierarchy( ):
                    l.set_hierarchy( True )
                
                return_list.append( l )
            return return_list
       
        if num == 1:
            for y in range(0, self.y_cell_count):
                k = ''
                if self.x is not None:
                    k = '0:'
                k =  k + str(y)

                if self.z is not None:
                    k = k+ ':0'

                cell = self.cells[k]
                tag = cell.getYtag()
                l = AxisLabel(tag, (0,y,0), tag, 1)
                
                if self.y.is_hierarchy():
                    l.set_hierarchy( True )
                
                return_list.append( l )
            return return_list
        
        if num == 0:
            rest = ''
            if self.num_dims == 2 : rest = ':0'
            if self.num_dims == 3 : rest = ':0:0'
            
            for x in range(0, self.x_cell_count):
                k = str(x) + rest
                cell = self.cells[k]
                tag = cell.getXtag()
                l = AxisLabel(tag, (x,0,0), tag, 0)
                
                if self.x.is_hierarchy():
                    l.set_hierarchy( True )
                
                return_list.append( l )

            return return_list
        

    def getCells(self):
        """
        Returns all the cells that the cube contains.
        """
        return self.cells
    
   
    def getCell(self, key):
        """
        Get cell in the cube by a cell key.
        """
        if not key in self.cells.keys():
            raise Exception('Key not found in dict')
        else:
            return self.cells[ key ]
   
    
    def __str__(self):
        for cell in self.get_cells().values():
            print '------------------------'
            print 'Image count', len(cell.getImages())
            print cell.key, 'Visiable image count', len(cell.getVisableImages())
        return ''
    
    
    
    def setLastClickedImage(self, image):
        self.last_clicked_image = image
        
    
    def getLastClickedImage(self):
        return self.last_clicked_image
     
    
    def addSelectedCell(self, cell):
        if not cell in self.selected_clusters:
            self.selected_clusters.append( cell )

    def getSelectedCells(self):
        return self.selected_clusters

    
    def clearSelectedClusters(self):
        self.selected_clusters = []
    
    
    def get_x_cell_count(self):
        return self.x_cell_count
    
    
    def get_y_cell_count(self):
        return self.y_cell_count

    
    def get_z_cell_count(self):
        return self.z_cell_count
    
    
    def getNumberOfImages(self):
        """
        Returns the number of images that the cube contains.
        """
        num = 0
        for cell in self.cells.values():
            num += len( cell.getImages() )
        return num
    
    
    def getVisibleImages(self):
        """
        Returns images that are visiable as lists hased by names.
        """
        images = dict()
        for cell in self.cells.values():
            for image in cell.getVisableImages():
                if image.get_location( ) not in images.keys(): 
                    images[image.get_location()] = list()
                images[image.get_location()].append(image)
                
        return images
        

    def setHoveredImage(self, image):
        self.currentHoveredImage = image
    
    def getHoveredImage(self):
        return self.currentHoveredImage
###########################################################################
