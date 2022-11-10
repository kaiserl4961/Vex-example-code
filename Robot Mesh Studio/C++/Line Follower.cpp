//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c8ac8f17a1f5796cf0b
// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::line       line_tracker_left(Brain.ThreeWirePort.A);
vex::line       line_tracker_right(Brain.ThreeWirePort.B);
vex::drivetrain dt(motor_left, motor_right, 319.1764, 292.1, vex::distanceUnits::mm);
//#endregion config_globals

//value returned when staring at a line:
int line_value = 60;
//value returned when staring at the floor:
int floor_value = 30;

bool sees_line(int tracker_value) {
    return abs(tracker_value - line_value) <= abs(tracker_value - floor_value);
}

int main(void) {
    //go slow, as this algorithm doesn't handle overshooting the line very well
    dt.setVelocity(10,velocityUnits::pct);
    while(true) {
        if(sees_line(line_tracker_left.value(pct))) {
            //left tracker saw line, we're drifting right
            dt.turn(turnType::left);
        } else if (sees_line(line_tracker_right.value(pct))) {
            //right tracker saw line, we're drifting left
            dt.turn(turnType::right);
        } else {
            //neither tracker sees the line, so we're straddling it
            dt.drive(fwd);
        }
    }
}
// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::line       line_tracker_left(Brain.ThreeWirePort.A);
vex::line       line_tracker_right(Brain.ThreeWirePort.B);
vex::drivetrain dt(motor_left, motor_right, 319.1764, 292.1, vex::distanceUnits::mm);
//#endregion config_globals

//value returned when staring at a line:
int line_value = 60;
//value returned when staring at the floor:
int floor_value = 30;

bool sees_line(int tracker_value) {
    return abs(tracker_value - line_value) <= abs(tracker_value - floor_value);
}

int main(void) {
    //go slow, as this algorithm doesn't handle overshooting the line very well
    dt.setVelocity(10,velocityUnits::pct);
    while(true) {
        if(sees_line(line_tracker_left.value(pct))) {
            //left tracker saw line, we're drifting right
            dt.turn(turnType::left);
        } else if (sees_line(line_tracker_right.value(pct))) {
            //right tracker saw line, we're drifting left
            dt.turn(turnType::right);
        } else {
            //neither tracker sees the line, so we're straddling it
            dt.drive(fwd);
        }
    }
}