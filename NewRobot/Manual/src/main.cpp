#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START IQ MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END IQ MACROS


// Robot configuration code.
inertial BrainInertial = inertial();
motor TL = motor(PORT3, false);
motor TR = motor(PORT4, false);
motor BL = motor(PORT2, false);
motor BR = motor(PORT1, false);
controller Controller = controller();



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

//----------------------------------------------------------------------------
//                                                                            
//    Module:       main.cpp                                                  
//    Author:       {author}                                                  
//    Created:      {date}                                                    
//    Description:  IQ project                                                
//                                                                            
//----------------------------------------------------------------------------

// Include the IQ Library
#include "iq_cpp.h"

// Allows for easier use of the VEX Library
using namespace vex;

float multi = 0.6;
int leftStrafe = 0;
int rightStrafe = 0;

void leftButtonPressed() {
  leftStrafe = 100;
}

void rightButtonPressed() {
  rightStrafe = -100;
}

void leftButtonReleased() {
  leftStrafe = 0;
}

void rightButtonReleased() {
  rightStrafe = 0;
}

void xdrive() {
  TL.setVelocity((-Controller.AxisD.position() + leftStrafe + rightStrafe) * multi, percent);
  TR.setVelocity((Controller.AxisA.position() - rightStrafe - leftStrafe) * multi, percent);
  BL.setVelocity((-Controller.AxisD.position() - leftStrafe - rightStrafe) * multi, percent);
  BR.setVelocity((Controller.AxisA.position() + rightStrafe + leftStrafe) * multi, percent);  
}

void setup() {
  TL.setMaxTorque(100, percent);
  TL.setStopping(hold);
  TL.setVelocity(0, percent);
  TL.spin(forward);

  TR.setMaxTorque(100, percent);
  TR.setStopping(hold);
  TR.setVelocity(0, percent);
  TR.spin(forward);

  BL.setMaxTorque(100, percent);
  BL.setStopping(hold);
  BL.setVelocity(0, percent);
  BL.spin(forward);

  BR.setMaxTorque(100, percent);
  BR.setStopping(hold);
  BR.setVelocity(0, percent);
  BR.spin(forward);
}

void turbo() {
  multi = 1.0;
}

void unturbo() {
  multi = 0.6;
}

int main() {
  Controller.ButtonL3.released(turbo);
  Controller.ButtonR3.released(unturbo);
  Controller.ButtonLUp.pressed(leftButtonPressed);
  Controller.ButtonLUp.released(leftButtonReleased);
  Controller.ButtonRUp.pressed(rightButtonPressed);
  Controller.ButtonRUp.released(rightButtonReleased);
  setup();
  while (true) {
    xdrive();
    wait(5, msec);
  }
}
