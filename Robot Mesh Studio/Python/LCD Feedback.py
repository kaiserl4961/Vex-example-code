#LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c70c8f17a1f57960b73
import vex
import sys

#region config
brain      = vex.Brain();
motor_arm  = vex.Motor(vex.Ports.PORT1, vex.GearSetting.RATIO18_1, False)
motor_claw = vex.Motor(vex.Ports.PORT10, vex.GearSetting.RATIO18_1, False)
con        = vex.Controller(vex.ControllerType.PRIMARY)
#endregion config

brain.screen.render() #enable double buffering for smoother drawing

while True:
  #arm control
  if con.buttonR1.pressing():
    #arm up
    motor_arm.spin(vex.DirectionType.FWD, 50, vex.VelocityUnits.PCT)
  elif con.buttonR2.pressing():
    #arm down
    motor_arm.spin(vex.DirectionType.REV, 50, vex.VelocityUnits.PCT)
  else:
    #arm hold position
    motor_arm.stop(vex.BrakeType.HOLD)
  #claw control
  if con.buttonL1.pressing():
    #claw one way (depends on motor installation)
    motor_claw.spin(vex.DirectionType.FWD, 50, vex.VelocityUnits.PCT)
  elif con.buttonL2.pressing():
    #claw other way
    motor_claw.spin(vex.DirectionType.REV, 50, vex.VelocityUnits.PCT)
  else:
    #claw hold position
    motor_claw.stop(vex.BrakeType.HOLD)
  # set current position as 0 on calibrate button (down) being pressed
  if con.buttonDown.pressing():
    motor_arm.set_rotation(0, vex.RotationUnits.DEG)
    motor_claw.set_rotation(0, vex.RotationUnits.DEG)
  #LCD feedback:
  # Each readout is divided by its gear ratio to
  # translate from motor rotation to arm/claw rotation
  brain.screen.clear_screen()
  brain.screen.set_cursor(0, 1)
  brain.screen.print_('Arm rotation: ' + str(float(motor_arm.rotation(vex.RotationUnits.DEG)) / 7) + ' degrees.')
  brain.screen.set_cursor(1, 1)
  brain.screen.print_('Claw rotation: ' + str(float(motor_claw.rotation(vex.RotationUnits.DEG)) / 3) + ' degrees.')
  brain.screen.render() #we're done drawing things, push them to the screen all at once