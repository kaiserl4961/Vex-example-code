//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c7bc8f17a1f579659df
// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      motor_arm(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::controller con(vex::controllerType::primary);
//#endregion config_globals


int main(void) {
    motor_arm.setVelocity(35,pct);
    while(true){
        if (con.ButtonL1.pressing()) {
            //Move arm towards upper limit (assuming arm started at the bottom)
            motor_arm.startRotateTo(110 * 7,deg);
        } else if (con.ButtonL2.pressing()) {
            //Move arm towards lower limit
            motor_arm.startRotateTo(0,deg);
        } else {
            //No driver input, so stop and hold position
            motor_arm.stop(hold);
        }
    }
}
