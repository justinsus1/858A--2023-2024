#include "vex.h";

int control(void);
double calculate(double, double);
void drive(double);

void turndeg(double angle = 90, int Ts = 100, double radius = -114, int driveDirection = 1, bool turnDirection = true);

void calibrateDrivetrain(void);

using namespace vex;
extern task controlLoop;
extern brain Brain;
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