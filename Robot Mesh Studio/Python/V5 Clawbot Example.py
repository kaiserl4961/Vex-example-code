#LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c6ec8f17a1f5795f60d
import vex

#region config
brain       = vex.Brain();
motor_arm   = vex.Motor(vex.Ports.PORT1, vex.GearSetting.RATIO18_1, False)
motor_claw  = vex.Motor(vex.Ports.PORT10, vex.GearSetting.RATIO18_1, False)
motor_right = vex.Motor(vex.Ports.PORT15, vex.GearSetting.RATIO18_1, True)
motor_left  = vex.Motor(vex.Ports.PORT16, vex.GearSetting.RATIO18_1, False)
con         = vex.Controller(vex.ControllerType.PRIMARY)
#endregion config

while True:
  #arm
  if con.buttonL1.pressing():
    # Raise arm
    motor_arm.spin(vex.DirectionType.FWD, 35, vex.VelocityUnits.PCT)
  elif con.buttonL2.pressing():
    # Lower arm
    motor_arm.spin(vex.DirectionType.REV, 35, vex.VelocityUnits.PCT)
  else:
    # Arm hold still
    motor_arm.stop(vex.BrakeType.HOLD)
  #claw
  if con.buttonR1.pressing():
    # Open claw
    motor_claw.spin(vex.DirectionType.FWD, 35, vex.VelocityUnits.PCT)
  elif con.buttonR2.pressing():
    # Close claw
    motor_claw.spin(vex.DirectionType.REV, 35, vex.VelocityUnits.PCT)
  else:
    # Claw hold still
    motor_claw.stop(vex.BrakeType.HOLD)
  # Right stick to right motor
  motor_right.spin(vex.DirectionType.FWD, (con.axis2.position(vex.PercentUnits.PCT)), vex.VelocityUnits.PCT)
  # Left stick to left motor
  motor_left.spin(vex.DirectionType.FWD, (con.axis3.position(vex.PercentUnits.PCT)), vex.VelocityUnits.PCT)
