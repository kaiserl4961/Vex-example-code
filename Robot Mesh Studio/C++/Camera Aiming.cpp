//SOURCE LINK : https://www.robotmesh.com/studio/5be40c89c8f17a1f5796cdcd
// VEX IQ C++ Project
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain             Brain;
vex::vision            vision_9(vex::PORT9);
vex::vision::signature sig_TARGETBLOB(1,101,3217,1659,-4681,-3869,-4275,2.3,0);
vex::motor             motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor             motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::drivetrain        dt(motor_left, motor_right, 319.1764, 292.1, vex::distanceUnits::mm);
//#endregion config_globals


int main(void) {
	//#region config_init
	vision_9.setBrightness(50);
	vision_9.setSignature(sig_TARGETBLOB);
	//#endregion config_init
	
    //camera image is 316 pixels wide, so the center is 316/2
    int screen_middle_x = 316 / 2;
    bool linedup = false;
    //take it slow
    dt.setDriveVelocity(10,vex::velocityUnits::pct);
    dt.setTurnVelocity(10,vex::velocityUnits::pct);
    while(not linedup) {
        //snap a picture
        vision_9.takeSnapshot(sig_TARGETBLOB);
        //did we see anything?
        if(vision_9.objectCount > 0) {
            //where was the largest thing?
            if(vision_9.largestObject.centerX < screen_middle_x - 5) {
                //on the left, turn left
                dt.turn(turnType::left);
            } else if (vision_9.largestObject.centerX > screen_middle_x + 5) {
                //on the right, turn right
                dt.turn(turnType::right);
            } else {
                //in the middle, we're done lining up
                linedup = true;
                dt.stop(coast);
            }
        } else {
            //saw nothing, relax
            dt.stop(coast);
        }
    }
}
