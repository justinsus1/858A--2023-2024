#include "vex.h"

using namespace vex;

extern brain Brain;
extern inertial BrainInertial;

extern motor leftMotorA;
extern motor leftMotorB ;
extern motor_group LeftDriveSmart;

extern motor rightMotorA;
extern motor rightMotorB;
extern motor_group RightDriveSmart;

extern smartdrive Drivetrain;

extern motor Ratchet_GearA;
extern motor Ratchet_GearB;
extern motor_group Ratchet_Gear;

extern touchled touch_led;

extern pneumatic pneumatic_system;

void touch();
void checkDevice();
void setup();