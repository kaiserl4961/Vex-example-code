#LINK TO SOURCE: https://www.robotmesh.com/studio/5be40d5ec8f17a1f579d1784
import vex
import sys

#region config
brain       = vex.Brain();
motor_right = vex.Motor(vex.Ports.PORT15, vex.GearSetting.RATIO18_1, False)
motor_left  = vex.Motor(vex.Ports.PORT16, vex.GearSetting.RATIO18_1, True)
dt          = vex.Drivetrain(motor_left, motor_right, 319.1764, 292.1, vex.DistanceUnits.MM)
con         = vex.Controller(vex.ControllerType.PRIMARY)
#endregion config

competition = vex.Competition()

def driver():
  # Place drive control code here, inside the loop
  while True:
    # This is the main loop for the driver control.
    # Each time through the loop you should update motor
    # movements based on input from the controller.
    motor_left.spin(vex.DirectionType.FWD, (con.axis3.position(vex.PercentUnits.PCT)), vex.VelocityUnits.PCT)
    motor_right.spin(vex.DirectionType.FWD, (con.axis2.position(vex.PercentUnits.PCT)), vex.VelocityUnits.PCT)
competition.drivercontrol(driver)

def auto():
  # Place autonomous code here
  dt.drive_for(vex.DirectionType.FWD, 24, vex.DistanceUnits.IN)
  dt.turn_for(vex.TurnType.LEFT, 180, vex.RotationUnits.DEG)
  dt.drive_for(vex.DirectionType.FWD, 24, vex.DistanceUnits.IN)
  dt.turn_for(vex.TurnType.LEFT, 180, vex.RotationUnits.DEG)
competition.autonomous(auto)


# main thread
# All activities that occur before competition start
# Example: setting initial positions
con.set_deadband(5, vex.PercentUnits.PCT)
dt.set_velocity(20, vex.VelocityUnits.PCT)