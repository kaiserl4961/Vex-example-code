//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c70c8f17a1f57960b98
// VEX V5 C++ Project
#include "vex.h"

//#region config_globals
vex::brain      Brain;
vex::motor      motor_arm(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor      motor_claw(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::controller con(vex::controllerType::primary);
//#endregion config_globals

using namespace vex;

int main(void) {
    Brain.Screen.render(true,false); //enable double buffering for smoother drawing
    motor_arm.setVelocity(50,velocityUnits::pct);
    motor_claw.setVelocity(50,velocityUnits::pct);
    while(true) {
        
        //claw control
        if(con.ButtonR1.pressing()) {
            motor_claw.spin(directionType::fwd);    //claw one way
        } else if(con.ButtonR2.pressing()) {
            motor_claw.spin(directionType::rev);    //claw other way
        } else {
            motor_claw.stop(brakeType::hold);       //claw hold
        }
        
        //arm control
        if(con.ButtonL1.pressing()) {
            motor_arm.spin(directionType::fwd);     //arm up
        } else if (con.ButtonL2.pressing()) {
            motor_arm.spin(directionType::rev);     //arm down
        } else {
            motor_arm.stop(brakeType::hold);        //arm hold
        }
        
        //calibrate position: set to 0 if button pressed
        if(con.ButtonDown.pressing()) {
            motor_arm.setRotation(0,rotationUnits::deg);
            motor_claw.setRotation(0,rotationUnits::deg);
        }
        
        //LCD feedback:
        //Each readout is divided by its gear ratio to translate from
        //motor rotation to arm/claw rotation
        Brain.Screen.clearLine(0,color::black);
        Brain.Screen.clearLine(1,color::black);
        Brain.Screen.setCursor(0,0);
        Brain.Screen.print("Arm rotation: %f degrees",motor_arm.rotation(rotationUnits::deg)/7.0);
        Brain.Screen.setCursor(1,0);
        Brain.Screen.print("Claw rotation: %f degrees",motor_claw.rotation(rotationUnits::deg)/3.0);
        Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
    }
}