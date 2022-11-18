#LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c8ac8f17a1f5796cf01
import vex
import math

#region config
brain              = vex.Brain();
motor_right        = vex.Motor(vex.Ports.PORT15, vex.GearSetting.RATIO18_1, True)
motor_left         = vex.Motor(vex.Ports.PORT16, vex.GearSetting.RATIO18_1, False)
line_tracker_left  = vex.Line(brain.three_wire_port.a)
line_tracker_right = vex.Line(brain.three_wire_port.b)
dt                 = vex.Drivetrain(motor_left, motor_right, 319.1764, 292.1, vex.DistanceUnits.MM)
#endregion config

#If the value of the left line tracker is closer to our target value than our floor value, this returns True
def left_sees_line():
  global line_value, floor_value_expected
  return math.fabs(line_tracker_left.value(vex.AnalogUnits.PCT) - line_value) <= math.fabs(line_tracker_left.value(vex.AnalogUnits.PCT) - floor_value_expected)

#If the value of the right line tracker is closer to our target value than our floor value, this returns True
def right_sees_line():
  global line_value, floor_value_expected
  return math.fabs(line_tracker_right.value(vex.AnalogUnits.PCT) - line_value) <= math.fabs(line_tracker_right.value(vex.AnalogUnits.PCT) - floor_value_expected)


# main thread
# Value returned when staring at a line:
line_value = 60
# Value returned when staring at the floor:
floor_value_expected = 30
# This algorithm does not handle error well,
# so go slowly...
dt.set_velocity(10, vex.VelocityUnits.PCT)
while True:
  if left_sees_line():
    # Left tracker saw line, we're drifting right
    dt.turn(vex.TurnType.LEFT)
  elif right_sees_line():
    # Right tracker saw line, we're drifting left
    dt.turn(vex.TurnType.RIGHT)
  else:
    # Neither sees the line, so we're straddling it
    dt.drive(vex.DirectionType.FWD)
