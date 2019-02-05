# Browser imports
from photocube.common.gui import createTextbox
from photocube.common.gui import createLabel
from photocube.common.gui import createDropDownList
from abstract import AbstractDialog
from photocube.objectcube import objectCubeService
from photocube.objectcube.framework import ObjectTag
from photocube.common import font




class ObjectTagDialog(AbstractDialog):
    """docstring for ObjectTagDialog"""
    
    
    def __init__(self, objectCubeObject):
        # create np for the dialog.
        np = aspect2d.attachNewNode('AddTagFilterDialog')
        AbstractDialog.__init__(self, np)         
        self.objectCubeObject = objectCubeObject 
        
        self.selectedTagsetName = None
        self.selectedTag = None


    def draw(self):
        self.__create_components()
        
        # set the position of the ok/cancel buttons
        self.create_ok_cancel_buttons()
        self.set_ok_button_pos((0.32, 1,-0.32))
        self.set_cancel_button_pos((0.45, 1, -0.32))
        
        
    def __create_components(self):
        """docstring for __create_components"""
        self.bg.setScale(0.60, 1 ,0.40)
        
        # Create label for dialog title.
        self.dialogTitleLabel = createLabel(parent=self.np, text='Add tag to image', bg=(0.4, 0.4 ,0.4, 0.5), fg=(1,1,1,1), scale=(0.033), pos=(-0.40, 0.32))
        
        # Create title for tagset dropdown
        createLabel(parent=self.np, text='Select tagset', fg=(1,1,1,1), scale=(0.030), pos=(-0.40, 0.20))
        
        # Get the name of all the user defined tagsets.
        tagsets = objectCubeService.getAllTagsets(onlyUserDefined=True)
        
        if len(tagsets) == 0:
            raise Expection('No tagset in database!')
        
        tagsetNames = [tagset.name for tagset in tagsets]
        
        # Create drop-down list for tagsets
        self.tagsetDropDown = createDropDownList(parent=self.np, text='select item', scale=0.035, text_scale=0.8, items=tagsetNames, initialitem=0, pos=(-0.52 ,1,0.13), onSelectChangeCommand=self.onTagsetDropDownItemSelectChange, frameSize=(0, 20, -0.5, 1), font=font)
        #self.selectedTagsetName = tagsetNames[0]
        
        # Create title for tag dropdown
        createLabel(parent=self.np, text='Select tag', fg=(1,1,1,1), scale=(0.030), pos=(-0.40, 0))
        
        # Create drop-down list for tags.
        self.tagsDropDown = createDropDownList(parent=self.np, text='Empty tagset', scale=0.035, text_scale=0.8, items=[], initialitem=0, pos=(-0.52,1,-0.06), onSelectChangeCommand=self.onTagDropDownItemSelectChange, frameSize=(0, 20, -0.5, 1), font=font)

        # Create title for tag textbox
        createLabel(parent=self.np, text='..or write a tag (for selected tagset)', fg=(1,1,1,1), scale=(0.030), pos=(-0.26, -0.20))
                
        # Create textbox for adding new tag
        self.txtTag = createTextbox(parent=self.np, width=20, text='', pos=(-0.52, 1, -0.27), scale=(0.035), focus=0)
        self.loadTagsIntoTagDropDownList(tagsets[0])
        
           
    
    def onTagsetDropDownItemSelectChange(self, item):
        """
        DocString for onTagsetDropDownItemSelectChange
        """
        print 'tagset drop down selectino changed'
        self.selectedTagsetName = item
        tagset = objectCubeService.getTagsetByName(self.selectedTagsetName)
        self.loadTagsIntoTagDropDownList(tagset)

    
    def onTagDropDownItemSelectChange(self, item):
        """
        DocString for onTagDropDownItemSelectChange
        """
        print 'tag dropdown changed'
        self.selectedTag = item


    def loadTagsIntoTagDropDownList(self, tagset):
        print 'taglist loaded'
        tags = tagset.getTags()
        if len(tags) > 0:
            self.tagsDropDown['items'] = [tag.valueAsString() for tag in tags] 
            self.selectedTag = self.tagsDropDown['items'][0]
        else:
            self.selectedTag = None
            self.tagsDropDown['items'] = list()
            self.tagsDropDown['text'] = 'Empty tagset'
            
            
        
     
    def click_ok_button(self):
        
        # Get the selected tagset
        selectedTagset = objectCubeService.getTagsetByName(self.selectedTagsetName)
        
        addingTag = None
        
        # Get the value of the tag textbox.
        tagTextValue = self.txtTag.get()
        
        # Check if we have some text in the tag box, if not we use the selection.
        if len(tagTextValue) > 0:
            addingTag = selectedTagset.fetchOrAddTag( tagTextValue )
        else:
            addingTag = selectedTagset.fetchOrAddTag( self.selectedTag )
        
        # add the tag to the object
        self.objectCubeObject.addTag(ObjectTag(addingTag))
        
        # Close the dialog.
        self.np.remove()
        messenger.send('dialog_closing')
        return