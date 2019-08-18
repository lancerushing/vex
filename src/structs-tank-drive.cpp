/**
 * Example of using a struct to maintain desired input state for tank drive
 */
#include "vex.h"

// Setup Robot
vex::brain Brain;
vex::motor motorL(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor motorR(vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::controller Controller1(vex::controllerType::primary);

// Define struct
struct inputsStruct {
    int left;   // left drive velocity
    int right;  // right drive velocity
};
struct inputsStruct inputs = {};  // initalize input sruct

// Thread to update the LCD on the brain
void showStatus() {
    int tick = 0; // just to see the screen update
    
    vex::brain::lcd s = Brain.Screen; // create a short variable "s"
    s.clearScreen();
    s.setFont(vex::fontType::mono15);

    while (true) {
        s.printAt(10, 20, "Tank Struct Example: % 6d", tick++);
        s.printAt(10, 40, "Inputs: Left: % 4d   Right: % 4d ", inputs.left, inputs.right);
        s.printAt(10, 60, "Motors: Left: % 4d   Right: % 4d ", 
            motorL.value(),
            motorR.value());
        vex::this_thread::sleep_for(100); // Let other threads run
    }
}

// Thread to set motors based on the input struct
void setDrive() {
     while (true) {
        motorL.spin(fwd, inputs.left, velocityUnits::pct);
        motorR.spin(fwd, inputs.right, velocityUnits::pct);
        vex::this_thread::sleep_for(10); // Let other threads run
     }
}

// listeners controller events

void setLeft() {
    inputs.left = Controller1.Axis3.value();
}
void setRight() {
    inputs.right = Controller1.Axis2.value();
}

// Setup all the listners in one place
void startControllerListeners() {
    Controller1.Axis3.change(setLeft);      
    Controller1.Axis2.change(setRight);
}


int main() {
    startControllerListeners();
    vex::thread threadStatus( showStatus );  
    vex::thread threadSetDrive( setDrive );
}
