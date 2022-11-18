//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c6ec8f17a1f5795f745
// VEX V5 C++ Project
#include "vex.h"

//#region config_globals
vex::brain      Brain;
vex::motor      motor_arm(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor      motor_claw(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::controller con(vex::controllerType::primary);
//#endregion config_globals

using namespace vex;

int main(void) {
    //these control the velocity the motor will pick when not given a velocity
    motor_arm.setVelocity(35,velocityUnits::pct);
    motor_claw.setVelocity(35,velocityUnits::pct);
    while(true) {
        
        //arm
        if(con.ButtonL1.pressing()) {
            //raise arm
            motor_arm.spin(directionType::fwd);
        } else if (con.ButtonL2.pressing()) {
            //lower arm
            motor_arm.spin(directionType::rev);
        } else {
            //hold position
            motor_arm.stop(brakeType::hold);
        }
        
        //claw
        if(con.ButtonR1.pressing()) {
            //open claw
            motor_claw.spin(directionType::fwd);
        } else if (con.ButtonR2.pressing()) {
            //close claw
            motor_claw.spin(directionType::rev);
        } else {
            //hold position
            motor_claw.stop(brakeType::hold);
        }
        
        //right drive motor
        motor_right.spin(directionType::fwd,con.Axis2.value(),velocityUnits::pct);
        
        //left drive motor
        motor_left.spin(directionType::fwd,con.Axis3.value(),velocityUnits::pct);
    }
}