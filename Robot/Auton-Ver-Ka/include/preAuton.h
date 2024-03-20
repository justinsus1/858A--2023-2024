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
extern motor basketRollerMotorA;
extern motor basketRollerMotorB;
extern motor_group basketRoller;
extern touchled touchLed;
extern pneumatic pneumatics;

void touch();
void checkDevice();
void setup();