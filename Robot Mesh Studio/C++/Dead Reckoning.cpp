//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c6ec8f17a1f5795f5d6
// VEX V5 C++ Project
#include "vex.h"
#include <cmath>

//#region config_globals
vex::brain      Brain;
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::drivetrain dt(motor_left, motor_right, 319.1764, 292.1, vex::distanceUnits::mm);
//#endregion config_globals

using namespace vex;

int main(void) {
    //set our standard velocity
    dt.setVelocity(20,vex::velocityUnits::pct);
    //advance four feet
    dt.driveFor(vex::directionType::fwd,48,vex::distanceUnits::in);
    vex::sleep(1);
    //retreat two feet
    dt.driveFor(vex::directionType::rev,24,vex::distanceUnits::in);
    vex::sleep(1);
    //set velocity a bit slower for more precision
    dt.setVelocity(10,vex::velocityUnits::pct);
    //turn to face a spot four feet to the right and two feet ahead
    //the result of calculating that angle has to be converted from radians to degrees by
    //multiplying by 180/pi
    dt.turnFor(vex::turnType::right,atan(48/24)*180/3.141592,vex::rotationUnits::deg);
    vex::sleep(1);
    //increase velocity again
    dt.setVelocity(20,vex::velocityUnits::pct);
    //drive along the hypotenuse of the triangle we used to compute our turn
    //if the length of the triangle's sides are a, b, and c, they are related by
    //a^2 + b^2 = c^2, so c, the side we want, is the square root of a^2 + b^2
    dt.driveFor(vex::directionType::fwd,sqrt(24*24+48*48),vex::distanceUnits::in);
    //after finishing a driveFor or turnFor command, the motors will stop in Hold
    //mode. To make them relax, you must explicitly stop them with another brakeType.
    dt.stop(vex::brakeType::coast);
}
