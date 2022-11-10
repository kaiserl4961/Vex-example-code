//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40d5ec8f17a1f579d1787
// VEX V5 C++ Project with Competition Template
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, false);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, true);
vex::drivetrain dt(motor_left, motor_right, 319.1764, 292.1, vex::distanceUnits::mm);
vex::controller con(vex::controllerType::primary);
//#endregion config_globals


// Creates a competition object that allows access to Competition methods.
vex::competition Competition;

void pre_auton() {
    // All activities that occur before competition start
    // Example: setting initial positions

}

void autonomous() {
    // Place autonomous code here
    dt.setVelocity(20,velocityUnits::pct);
    dt.driveFor(fwd,24,distanceUnits::in);
    dt.turnFor(turnType::left,180,deg);
    dt.driveFor(fwd,24,distanceUnits::in);
    dt.turnFor(turnType::left,180,deg);
}

void drivercontrol() {
    // Place drive control code here, inside the loop
    while (true) {
        // This is the main loop for the driver control.
        // Each time through the loop you should update motor
        // movements based on input from the controller.
        motor_left.spin(fwd,con.Axis3.position(pct),pct);
        motor_right.spin(fwd,con.Axis2.position(pct),pct);
    }
}

int main() {
    // Do not adjust the lines below

    // Set up (but don't start) callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Robot Mesh Studio runtime continues to run until all threads and
    // competition callbacks are finished.
    
    con.setDeadband(5,pct);
}