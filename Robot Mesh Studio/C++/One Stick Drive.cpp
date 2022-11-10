//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c6ec8f17a1f5795f523
// VEX V5 C++ Project
#include "vex.h"

//#region config_globals
vex::brain      Brain;
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::controller con(vex::controllerType::primary);
//#endregion config_globals

using namespace vex;

int main(void) {
    while(true) {
        //Left motor, vertical axis of left joystick plus horizontal axis of left joystick
        motor_left.spin(vex::directionType::fwd,
            con.Axis3.position(vex::percentUnits::pct) + con.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);
        //Right motor, vertical axis of left joystick minus horizontal axis of left joystick
        motor_right.spin(vex::directionType::fwd,
            con.Axis3.position(vex::percentUnits::pct) - con.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);
    }
}