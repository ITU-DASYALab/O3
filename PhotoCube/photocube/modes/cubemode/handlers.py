from pandac.PandaModules import WindowProperties
from direct.task import Task


class FloatingCameraHandler:
    def __init__(self):
        self.enabled = False
        self.keys_status = dict()
        self.prevtime = 0
    
    def enable(self):
        
        if not self.isEnabled():
            base.win.movePointer(0, base.win.getXSize()/2, base.win.getYSize()/2)
            self.enabled = True
            base_properties = base.win.getProperties()
            props = WindowProperties()
            props.setCursorHidden(True)
            base.win.requestProperties(props)

            self.prev_time = 0
            self.speed = 30

            self.x = base.mouseWatcherNode.getMouseX()
            self.y =base.mouseWatcherNode.getMouseY()

            # start the freefloat mouse task.
            self.free_look_task = base.taskMgr.add(self.mouseWatcherWindowMode, 'cubemode/flycamera/mouse')
            self.free_look_kb_task = base.taskMgr.add(self.kbTask, 'cubemode/flycamera/keyboard')
            
            # start the keyboard task
            for x in 'wsadf':
                self.keys_status[x] = False
            
            base.accept('w', self.eventW)
            base.accept('w-up', self.eventWup)  
            base.accept('s', self.eventS)
            base.accept('s-up', self.eventSup)
            base.accept('a', self.eventA)
            base.accept('a-up', self.eventAup)
            base.accept('d', self.eventD)
            base.accept('d-up', self.eventDup)
            base.accept('escape', self.disable)

        
    
    
    def disable(self):
        # Stop the mouse and kb tasks.
        self.enabled = False

        # ignore events
        base.ignore('w')
        base.ignore('w-up')  
        base.ignore('s')
        base.ignore('s-up')
        base.ignore('a',)
        base.ignore('a-up')
        base.ignore('d')
        base.ignore('d-up')
        
        # Stop the camera task!
        taskMgr.remove(self.free_look_task)
        taskMgr.remove(self.free_look_kb_task)
        
        # Reset the camera position!!


        # show the mouse again
        props = WindowProperties()
        props.setCursorHidden(False)
        base.win.requestProperties(props)

        


    
    
    def isEnabled(self):
        return self.enabled


    def kbTask(self, task):
        speed = 50
        elapsed = task.time - self.prevtime
        
        forward = base.camera.getNetTransform().getMat().getRow3(1)
        forward.normalize()
       
        if self.keys_status['w']:
            base.camera.setPos(base.camera.getPos() + (forward*(elapsed*speed)))
 
        if self.keys_status['s']:
             base.camera.setPos(base.camera.getPos() - (forward*(elapsed*speed)))

        if self.keys_status['a']:
            dir = base.camera.getMat().getRow3(0) 
            base.camera.setPos(base.camera.getPos() - (dir*(elapsed*speed)/2))

        if self.keys_status['d']:
            dir = base.camera.getMat().getRow3(0) 
            base.camera.setPos(base.camera.getPos() + (dir*(elapsed*speed)/2))
        
        self.prevtime = task.time 
        return Task.cont




    def mouseWatcherWindowMode(self, task):
        elapsed = task.time - self.prev_time
        if base.mouseWatcherNode.hasMouse():
            self.x=base.mouseWatcherNode.getMouseX()
            self.y=base.mouseWatcherNode.getMouseY()
            
            if(self.x > 0):
                base.camera.setH(base.camera.getH()-(elapsed*self.speed*(self.x * self.speed)))
                #messenger.send('camera_moved')

            
            if(self.x<0):
                base.camera.setH(base.camera.getH()-(elapsed*self.speed*(self.x * self.speed)))
                #messenger.send('camera_moved')

            if(self.y>0):
                base.camera.setP(base.camera.getP()+(elapsed*self.speed * (self.y*self.speed)))
                #messenger.send('camera_moved')

            if(self.y<0):
                base.camera.setP(base.camera.getP()+(elapsed*self.speed * (self.y*self.speed)))
                #messenger.send('camera_moved')
 
            # Set the mouse back to it's inital place.
            base.win.movePointer(0, base.win.getXSize()/2, base.win.getYSize()/2)
            self.prev_time = task.time
        
        return Task.cont


    def eventW(self):
        self.keys_status['w'] = True

    def eventWup(self):
        self.keys_status['w'] = False

    def eventS(self):
        self.keys_status['s'] = True

    def eventSup(self):
        self.keys_status['s'] = False

    def eventA(self):
        self.keys_status['a'] = True

    def eventAup(self):
        self.keys_status['a'] = False

    def eventD(self):
        self.keys_status['d'] = True

    def eventDup(self):
        self.keys_status['d'] = False






class CellScroller:
    
    def __init__(self):
        print 'Create Scroller'
    
    def enable(self):
        base.accept('wheel_up', self.onMouseWheelUp)
        base.accept('wheel_down', self.onMouseWheelDown)
    
    def disable(self):
        base.ignore('wheel_up')
        base.ignore('wheel_down')

    def getScrollMessage(self):
        return 'CellScroller/ScrollingMouse'
    
    def onMouseWheelUp(self):
        messenger.send(self.getScrollMessage(), ['up'])

    def onMouseWheelDown(self):
        messenger.send(self.getScrollMessage(), ['down'])

        






class CubeScaler:
    def __init__(self):
        print 'CubeScaler created'
    
    def enable(self):
        base.accept('shift-wheel_up', self.message_shift_scroll_up)
        base.accept('shift-wheel_down', self.message_shift_scroll_down)
    
    def disable(self):
        base.ignore('shift-wheel_up')
        base.ignore('shift-wheel_down')
    
    def getScaleEventMessage(self):
        return 'cubemode_plugin_cube_scaler_scale_up'
    
    def message_shift_scroll_down(self):
        messenger.send(self.getScaleEventMessage(), ['down'])
        
    def message_shift_scroll_up(self):
        messenger.send(self.getScaleEventMessage(), ['up'])





class CubeMouseRotater:
    def __init__(self, np=None):
        # Member variables
        self.rotating_np = np
        self.rotating = False
    
    def setRotatingNp(self, np):
        self.rotating_np = np
    
    def enable(self):
        print 'enabling coordinate rotation on np', self.rotating_np
        # Needed for Linux.
        #base.accept('lcontrol', self.event_ctrl_down)
        #base.accept('lcontrol-up', self.event_ctrl_up)
        
        # Needed for mac.
        base.accept('control', self.event_ctrl_down)
        base.accept('control-up', self.event_ctrl_up)
    
    
    def disable(self):
        base.ignore('control')
        base.ignore('control-up')

    
    def isRotating(self):
        return self.rotating
    
    def event_ctrl_down(self):
        print 'ctrl_down'
        self.rotating = True
        self.enable_rot()
    
    def event_ctrl_up(self):
        print 'ctrl_up'
        self.rotating = False
        self.disable_rot()
    
    def disable_rot(self):
        if self.free_look_task is not None:
            taskMgr.remove(self.free_look_task)

        # show the mouse cursor again.
        props = WindowProperties()
        props.setCursorHidden(False)
        base.win.requestProperties(props)


    def enable_rot(self):
        # get the current mouse pos.
        self.mouse_x = base.mouseWatcherNode.getMouseX()
        self.mouse_y = base.mouseWatcherNode.getMouseY()

        #print 'mouse: enabling freelook.'
        self.mouse_freefloat_enabled = True
        self.prev_time = 0
        self.speed = 10

        props = WindowProperties()
        props.setCursorHidden(True)
        #props.setMouseMode(WindowProperties.MRelative)
        base.win.requestProperties(props)
        self.free_look_task = base.taskMgr.add(self.mouse_rot_coordinate_task, 'freeLook')



    def mouse_rot_coordinate_task(self, task):
        elapsed = task.time - self.prev_time
        if base.mouseWatcherNode.hasMouse():
            x= base.mouseWatcherNode.getMouseX() #- self.mouse_x
            y= base.mouseWatcherNode.getMouseY() #- self.mouse_y

            if(x>0):
                messenger.send('coordinate_hpr_changed')
                np = self.rotating_np
                np.setH(np.getH()+ (elapsed*self.speed*(x*self.speed)))
                #print browser.coordinate.coordinateService.get_coordinate().np.setR 

            if(x<0):
                messenger.send('coordinate_hpr_changed')
                np = self.rotating_np
                np.setH(np.getH()+ (elapsed*self.speed*(x*self.speed)) )

            if(y<0):
                messenger.send('coordinate_hpr_changed')
                np = self.rotating_np
                np.setP(np.getP()-(elapsed*self.speed*(y*self.speed)) )

            if(y>0):
                messenger.send('coordinate_hpr_changed')
                np = self.rotating_np
                np.setP(np.getP()-(elapsed*self.speed*(y*self.speed)) )


            # Set the mouse back to it's inital place.
            self.prev_time = task.time

            # get the current mouse pos.
            #print x,y
            base.win.movePointer(0, base.win.getXSize()/2, base.win.getYSize()/2)
            self.mouse_x = base.mouseWatcherNode.getMouseX()
            self.mouse_y = base.mouseWatcherNode.getMouseY()

        return Task.cont  


