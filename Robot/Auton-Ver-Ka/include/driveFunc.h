#include "vex.h";

#define WIDTH 228
#define GEAR_RATIO 2
#define WHEEL_SIZE 200

extern vex::task controlLoop;

int control(void);
double calculate(double, double);
void drive(double driveTarget, double maxVel = 100);
void turndeg(double angle = 90, int Ts = 100, double radius = -114, int driveDirection = 1, bool turnDirection = true, bool waiting = true, int time = 0);
void calibrateDrivetrain(void);