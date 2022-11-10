#LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c7ac8f17a1f57964f74
import vex

#region config
brain     = vex.Brain();
motor_arm = vex.Motor(vex.Ports.PORT1, vex.GearSetting.RATIO18_1, False)
con       = vex.Controller(vex.ControllerType.PRIMARY)
#endregion config

# main thread
motor_arm.set_velocity(35, vex.VelocityUnits.PCT)
while True:
  if con.buttonL1.pressing():
    # Move towards the arm's upper limit
    # (Assumes arm started at bottom)
    motor_arm.start_rotate_to((110 * 7), vex.RotationUnits.DEG)
  elif con.buttonL2.pressing():
    # Move towards the arm's lower limit
    # (Assumes arm started at bottom)
    motor_arm.start_rotate_to(0, vex.RotationUnits.DEG)
  else:
    # No driver input, so stop the arm and hold position
    motor_arm.stop(vex.BrakeType.HOLD)