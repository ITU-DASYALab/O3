class WallMode( AbstractMode ):
    
    def __init__(self, enable_key):
        AbstractMode.__init__(self, 'WallMode', enable_key)


    def enable(self):
        print '-- enabling mode', self.mode_name