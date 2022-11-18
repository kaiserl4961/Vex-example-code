//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c75c8f17a1f57963006
// VEX V5 C++ Project
#include "vex.h"

//#region config_globals
vex::brain      Brain;
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::bumper     bumper_back(Brain.ThreeWirePort.A);
vex::drivetrain dt(motor_left, motor_right, 319.1764, 292.1, vex::distanceUnits::mm);
//#endregion config_globals

using namespace vex;

int main(void) {
    dt.setVelocity(20,velocityUnits::pct); //take it slow
    while(true) {
        //creep backwards...
        dt.drive(directionType::rev);
        while(!bumper_back.pressing()){} //wait for bumper to be pressed
        dt.drive(directionType::fwd);
        sleep(2); //drive away for two seconds
        dt.turnFor(turnType::left,77,rotationUnits::deg); //turn to avoid obstacle
        //ready for another try
    }
}