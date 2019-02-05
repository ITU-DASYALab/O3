from sys import argv
from interfaces import Clickable, Hoverable
from datetime import datetime

# Axis constants.
X_AXIS, Y_AXIS, Z_AXIS = range(3)

# Common resrouces used withing the application.
font = loader.loadFont('Arial.ttf')
tagTexture = loader.loadTexture("static/images/dlg_window_bg.tif")


def error_output(message, prefix=None):
    ts = datetime.now()
    _ts = str(ts.day) +'/'+str(ts.month) + '/' + str(ts.year) + ' ' + str(ts.hour) + ':' + str(ts.minute) + ':' + str(ts.second)
    if prefix is not None:
        print '[!ERROR!]['+_ts+'][' + prefix +']: ' + message
    else:
        print '[!ERROR!]['+_ts+']: ' + message
