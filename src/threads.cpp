/**
 * Example of how to start multiple threads.
 * @author Lance Rushing <lancerushing@gmail.com>
 * @see https://github.com/lancerushing/vex
 */

#include "vex.h"

// Configure Robot Hardware
vex::brain Brain;

void myThread1() {
    int count = 0;
  
    while(true) {
        Brain.Screen.printAt(10, 40, "myThread1 %d", count++);
      
        vex::this_thread::sleep_for(100); // Sleep, and let other threads run
    }
}

void myThread2() {
    int count = 0;
   
    while(true) {
        Brain.Screen.printAt(10, 60, "myThread2 %d", count++);
   
        vex::this_thread::sleep_for(200); // Sleep, and let other threads run
    }
}

int main() {
    // start the threads
    vex::thread t1( myThread1 );
    vex::thread t2( myThread2 ); 

    Brain.Screen.printAt(0, 110, "Theads have Started.");
    
    // Wait, then stop (interrupt) the threads 
    vex::this_thread::sleep_for(10000); // 10 seconds
    t1.interrupt();
    t2.interrupt();

    Brain.Screen.printAt(0, 130, "All Done");

    // Note: The program will only end if all threads are stopped
}