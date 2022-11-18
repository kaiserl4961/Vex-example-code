//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c90c8f17a1f5796fcae
// VEX V5 C++ Project
#include "vex.h"
#include <algorithm>
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      back_right_motor(vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor      back_left_motor(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor      front_right_motor(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor      front_left_motor(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::controller con(vex::controllerType::primary);
//#endregion config_globals


int main(void) {
    while(true) {
        
        //Get the raw sums of appropriate joystick axes
        double front_left = (double)(con.Axis3.position(pct) + con.Axis4.position(pct) + con.Axis1.position(pct));
        double back_left = (double)(con.Axis3.position(pct) - con.Axis4.position(pct) + con.Axis1.position(pct));
        double front_right = (double)(con.Axis3.position(pct) - con.Axis4.position(pct) - con.Axis1.position(pct));
        double back_right = (double)(con.Axis3.position(pct) + con.Axis4.position(pct) - con.Axis1.position(pct));
        
        //Find the largest raw sum or 100
        double max_raw_value = std::max(front_left,std::max(back_left,std::max(front_right,std::max(back_right,100.0))));
        
        //Scale down each value if there was one larger than 100, otherwise leave them alone
        //The largest value will be scaled down to 100, and the others will be reduced by the same factor
        front_left = front_left / max_raw_value * 100;
        back_left = back_left / max_raw_value * 100;
        front_right = front_right / max_raw_value * 100;
        back_right = back_right / max_raw_value * 100;
        
        //Write the scaled sums out to the various motors
        front_left_motor.spin(fwd, front_left, velocityUnits::pct);
        back_left_motor.spin(fwd, back_left, velocityUnits::pct);
        front_right_motor.spin(fwd, front_right, velocityUnits::pct);
        back_right_motor.spin(fwd, back_right, velocityUnits::pct);
    }
}