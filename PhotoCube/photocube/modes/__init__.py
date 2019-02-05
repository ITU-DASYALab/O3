from services import ModeService
from mode import *
from cubemode.mode import *
from cardmode import *
from shooter import *

# Create instance of the mode service.
modeService = ModeService()

# Create and register the cube mode.
cardMode = CardMode('CardMode')
modeService.register_mode( cardMode )

# Create, and register instance of the Card mode.
cubeMode = CubeMode('CubeMode')
modeService.register_mode( cubeMode )

# Create, and register instance of the Shooter mode.
shooterMode = ShooterMode('ShooterMode')
modeService.register_mode( shooterMode )

