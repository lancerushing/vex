/**
 * Example of using fixed functions to drive tank
 * Useful in creating autonomous instructions
 * @author Lance Rushing <lancerushing@gmail.com>
 */
#include "vex.h"

// Setup Robot
vex::brain Brain;
vex::motor motorL(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor motorR(vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::controller Controller1(vex::controllerType::primary);

// custom variables
double turnVelocity = 50; // how fast to spin the motors for turning
double moveVelocity = 50; // how fast to spin the motors for moving

// Thread to update the LCD on the brain
void showStatus() {
    int tick = 0;
    
    vex::brain::lcd s = Brain.Screen; // create a short variable "s"
    s.clearScreen();
    s.setFont(vex::fontType::mono15);

    while (true) {
        s.printAt(10, 20, "Tank Training: % 6d", tick++);
        s.printAt(10, 60, "Motors: Left: % 4d   Right: % 4d ", 
            motorL.value(),
            motorR.value());

        vex::this_thread::sleep_for(100); // Let other threads run
    }
}

void stopMotors() {
    motorL.stop(vex::brakeType::brake);
    motorR.stop(vex::brakeType::brake);
}

void turnLeft() {
    motorL.rotateFor(-1, rotationUnits::rev, turnVelocity, vex::velocityUnits::pct, false);
    motorR.rotateFor(1, rotationUnits::rev, turnVelocity, vex::velocityUnits::pct, true);
}

void turnRight() {
    motorL.rotateFor(1, rotationUnits::rev, turnVelocity, vex::velocityUnits::pct, false);
    motorR.rotateFor(-1, rotationUnits::rev, turnVelocity, vex::velocityUnits::pct, true);
}

void moveForward() {
    motorL.rotateFor(1, rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
    motorR.rotateFor(1, rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, true);
}

void moveBackward() {
    motorL.rotateFor(-1, rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
    motorR.rotateFor(-1, rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, true);
}

void startControllerListeners() {
    Controller1.ButtonUp.pressed(moveForward);      
    Controller1.ButtonDown.pressed(moveBackward);      
    Controller1.ButtonLeft.pressed(turnLeft);      
    Controller1.ButtonRight.pressed(turnRight);      
}

int main() {
    vex::thread threadStatus( showStatus );  
    startControllerListeners();
}
