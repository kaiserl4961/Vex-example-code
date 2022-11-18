//LINK TO SOURCE: https://www.robotmesh.com/studio/5be40c89c8f17a1f5796c976
// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      motor_arm(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor      motor_claw(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::controller con(vex::controllerType::primary);
//#endregion config_globals

void armthread() {
    //arm thread
    motor_arm.setVelocity(50,pct);
    while (true) {
        if(con.ButtonL1.pressing()) {
            motor_arm.spin(fwd);
        } else if(con.ButtonL2.pressing()) {
            motor_arm.spin(directionType::rev);
        } else {
            motor_arm.stop(hold);
        }
    }
}

void clawthread() {
    //claw thread
    motor_claw.setVelocity(50,pct);
    while(true) {
        if (con.ButtonR1.pressing()) {
            motor_claw.spin(fwd);
        } else if (con.ButtonR2.pressing()) {
            motor_claw.spin(directionType::rev);
        } else {
            motor_claw.stop(hold);
        }
    }
}

void forkedthread() {
    //we will start this twice to demonstrate thread forking and independence
    int i = 0; //this variable isn't global, so each copy of this function has its own copy of i
    while(true) {
        sleep(1);
        printf("%d\r\n",i);
        i++;
    }
}

int main(void) {
    // Start here
    //To start a thread, we instantiate the thread class using the
    //function to run as an argument to the constructor, as follows:
    thread m_armthread = thread(armthread);
    thread m_clawthread = thread(clawthread);
    thread m_forkedthread1 = thread(forkedthread);
    thread m_forkedthread2 = thread(forkedthread);
    
    //now use this main thread to control the drive train
    while(true) {
        motor_right.spin(fwd,con.Axis2.position(pct),pct);
        motor_left.spin(fwd,con.Axis3.position(pct),pct);
    }
}