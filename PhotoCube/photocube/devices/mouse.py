from direct.showbase import DirectObject
from pandac.PandaModules import *
from direct.task import Task
from pandac.PandaModules import WindowProperties
from photocube.dialogs import dialogService



#############################################################
class MouseObjectPicker(DirectObject.DirectObject):
    def __init__(self, root=render, messagePrefixMouse1='CLICK_MOUSE1_', messagePrefixMouse2='CLICK_MOUSE2_', messagePrefixMouse3='CLICK_MOUSE3_'):
        """
        Constructor fro the MouseObjectPicker class.
        """
        # Member variables for message prefixes.
        self.messagePrefixMouse1 = messagePrefixMouse1
        self.messagePrefixMouse2 = messagePrefixMouse2
        self.messagePrefixMouse3 = messagePrefixMouse3
        
        # Member variables for raytracing and clicking.  
        self.root = root
        self.picker= CollisionTraverser()
        self.queue=CollisionHandlerQueue()
        self.pickerNode=CollisionNode('mouseRay')
        self.pickerNP=camera.attachNewNode(self.pickerNode)
        self.pickerNode.setFromCollideMask(GeomNode.getDefaultCollideMask())
        self.pickerRay=CollisionRay()
        self.pickerNode.addSolid(self.pickerRay)
        self.picker.addCollider(self.pickerNP, self.queue)
      
        # Accept mouse click events.
        self.accept('mouse3', self.event_rightClick)
        self.accept('mouse1', self.event_leftClick)
        self.accept('mouse1-up', self.event_leftClick_up)
      
   
   
    def makeRightPickable(self, newObj):
        """
        todo: add comment.
        """
        newObj.setTag('pickable_right','true')
        #print 'MouseObjectPicker: object made right pickable', newObj
        return self.messagePrefixMouse3 + str(newObj)
   

    def makeLeftPickable(self,newObj):
        """
        Add comment.
        """
        newObj.setTag('pickable_left','true')
        #print 'MouseObjectPicker: object made left pickable', newObj
        return self.messagePrefixMouse1 + str(newObj)
   
   
   
   
    def get_object_hit(self, mpos, tag): #mpos is the position of the mouse on the screen
        picker_object=None #be sure to reset this
        self.pickerRay.setFromLens(base.camNode, mpos.getX(),mpos.getY())
        self.picker.traverse(self.root)

        if self.queue.getNumEntries() > 0:
            self.queue.sortEntries()
            picker_object=self.queue.getEntry(0).getIntoNodePath()

            parent = picker_object.getParent()
            picker_object=None

            while parent != self.root:
                if parent.getTag(tag)=='true':
                    picker_object=parent
                    #print 'mess',message
                    #messenger.send("context_click")
                    return parent
                else:
                    parent=parent.getParent()
        return None


    
    
    def event_rightClick(self):
        """
        What is this?
        """
        if not dialogService.hasOpenDialog():
            p = self.get_object_hit( base.mouseWatcherNode.getMouse(), 'pickable_right')
            message = self.messagePrefixMouse3 + str(p)
            messenger.send(message, [p])
            print message

    
    def event_leftClick(self):
        """
        What is this?
        """
        if not dialogService.hasOpenDialog():
            p = self.get_object_hit( base.mouseWatcherNode.getMouse(), 'pickable_left')
            message = self.messagePrefixMouse1 + str(p)
            messenger.send(message, [p])

    def event_leftClick_up(self):
        if not dialogService.hasOpenDialog():
            p = self.get_object_hit( base.mouseWatcherNode.getMouse(), 'pickable_left-up')
            message = self.messagePrefixMouse1 + str(p)
            message = '%s%s-up' % (self.messagePrefixMouse1, str(p))
            messenger.send(message, [p])
#############################################################











#############################################################
class MouseOverWatcher(DirectObject.DirectObject):
   
   def __init__(self, root=render):
      
      # Prefix for hover and leave
      self.hoverPrefix = 'zoomin_'
      self.leavePrefix = 'zoomout_'
      
      # Createing zoomer node and queue and stuff.
      self.root = root
      self.zoomer = CollisionTraverser()
      self.queue = CollisionHandlerQueue()
      self.zoomerNode=CollisionNode('zoomer_mouseRay')
      self.zoomerNP=camera.attachNewNode(self.zoomerNode)
      self.zoomerNode.setFromCollideMask(GeomNode.getDefaultCollideMask())
      self.zoomerRay=CollisionRay()
      self.zoomerNode.addSolid(self.zoomerRay)
      self.zoomer.addCollider(self.zoomerNP, self.queue)

      #this holds the object that has been picked
      self.zoomerObj=None
      

   def makeObjectMouseAware(self,newObj):
      """
      What is this?
      """
      newObj.setTag('mouse_overable','true')
      hoverMessage = self.hoverPrefix+str(newObj)
      leaveMessage = self.leavePrefix+str(newObj)
      return (hoverMessage, leaveMessage)


   def get_object_hit(self, mpos): #mpos is the position of the mouse on the screen
      self.pickedObj=None #be sure to reset this
      self.zoomerRay.setFromLens(base.camNode, mpos.getX(),mpos.getY())
      self.zoomer.traverse(self.root)
      if self.queue.getNumEntries() > 0:
         self.queue.sortEntries()
         self.zoomerObj=self.queue.getEntry(0).getIntoNodePath()

         parent=self.zoomerObj.getParent()
         self.zoomerObj=None
         
         while parent != self.root:
            if parent.getTag('mouse_overable')=='true':
               self.pickedObj=parent
               messenger.send("hit")
               return parent
            else:
               parent=parent.getParent()
      return None
#############################################################











#############################################################
class MouseHandler:
    
    "THIS IS THE MAIN MOUSE HANDLING SERVICE CLASS!!! ALL MUST GO THROUGH THIS ONE!!!"
    
    def __init__(self):
        """
        Constructor for the MouseHandler. Create instance of MouseOverWatcher and
        MouseObjectPicker.
        """
        # Create instance of the MouseOverWatcher.
        self.mouseOverWathcer = MouseOverWatcher()
        
        #self.mouseOverWathcer.hoverPrefix
        #self.mouseOverWatcher.leavePrefix
        
        # List that contains message strings
        self.messages = []
        
        # Member variables
        #self.mouse_freefloat_enabled = False
        #self.free_look_task = None
        #self.mouse_looker_task_zoom = None
        self.mouse_over_node = None
        
        # task for mouse over watcher.
        self.mouse_over_watcher_task = base.taskMgr.add(self.mouse_over_watcher_task, 'mouse_over_watcher_task')
        
        # Member variable for the context picker
        self.mouseObjectPicker = MouseObjectPicker()
       
        # Member variable for mouse cluster idle exploit
        #self.idle_exploit_task = None
        #self.has_exploit = None
        #self.last_pos = None
        #self.is_idle_exploit_enabled = False


    
    
    
    
    def makeNPPickableRight(self, np):
        """
        What is this?
        """
        return self.mouseObjectPicker.makeRightPickable(np)

    
    def makeNPPickableLeft(self, np):
        """
        """
        return self.mouseObjectPicker.makeLeftPickable(np)
    
    def makeNPMouseHoverable(self, np):
        """
        Function for making nodepath mouse overable.
        """
        return self.mouseOverWathcer.makeObjectMouseAware(np)    
    
    
    
    
    
    def mouse_over_watcher_task(self, task):
        """
        What is this?
        """
        # If there is any dialog open, we will not do anything!
        if dialogService.hasOpenDialog():
            return task.cont

        
        #if self.last_pos is None:
        #    if not base.mouseWatcherNode.hasMouse():
        #        return task.cont
            
            # Get the mouse coordinates. 
            x=base.mouseWatcherNode.getMouseX()
            y=base.mouseWatcherNode.getMouseY()
            
        
        if base.mouseWatcherNode.hasMouse():
            curr_pos = (base.mouseWatcherNode.getMouseX(),base.mouseWatcherNode.getMouseY())
            self.last_pos = curr_pos
            
            if self.mouseOverWathcer.get_object_hit(base.mouseWatcherNode.getMouse()) is None:
                
                if self.mouse_over_node is not None:
                    messenger.send(self.mouseOverWathcer.leavePrefix+str(self.mouse_over_node), [self.mouse_over_node])
                    #print "zoomout_"+str(self.mouse_over_node)
                    self.mouse_over_node = None 
            
                else:
                    messenger.send(self.mouseOverWathcer.leavePrefix + "none")
                    #print 'zoomout_none'
            else:
                
                if self.mouse_over_node is not None and self.mouse_over_node != self.mouseOverWathcer.get_object_hit(base.mouseWatcherNode.getMouse()):
                    messenger.send(self.mouseOverWathcer.leavePrefix+str(self.mouse_over_node), [self.mouse_over_node])
                    #print "zoomout_"+str(self.mouse_over_node)
                
                if self.mouse_over_node != self.mouseOverWathcer.get_object_hit(base.mouseWatcherNode.getMouse()):
                    self.mouse_over_node = self.mouseOverWathcer.get_object_hit(base.mouseWatcherNode.getMouse())
                    messenger.send(self.mouseOverWathcer.hoverPrefix + str(self.mouse_over_node), [self.mouse_over_node])
                    #print "zoomin_"+str(self.mouse_over_node)
        return task.cont

    
    

#############################################################
