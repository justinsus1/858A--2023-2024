#include "vex.h";

extern vex::task controlLoop;

int control(void);
double calculate(double, double);
void drive(double driveTarget, double maxVel = 100);
void turndeg(double angle = 90, int Ts = 100, double radius = -114, int driveDirection = 1, bool turnDirection = true);
void calibrateDrivetrain(void);