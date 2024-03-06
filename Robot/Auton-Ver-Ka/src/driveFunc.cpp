#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vex.h"

using namespace vex;

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

// Robot configuration code.
inertial BrainInertial = inertial();

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       justin_sus1                                               */
/*    Created:      10/23/2023, 7:48:46 PM                                    */
/*    Description:  IQ2 project                                               */
/*                  -                                                          */
/*---------------------------------------------------------------------------*/


// define your global instances of motors and other devices here
brain Brain;
motor leftMotorA = motor(PORT4, 2.5, true);
motor leftMotorB = motor(PORT2, 2.5, true);

motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);


motor rightMotorA = motor(PORT10, 2.5, false);
motor rightMotorB = motor(PORT11, 2.5, false);

motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, BrainInertial, 200);

motor basketRollerMotorA = motor(PORT8, false);
motor basketRollerMotorB = motor(PORT2, true);
motor_group basketRoller = motor_group(basketRollerMotorA, basketRollerMotorB);

touchled touchLed = touchled(PORT6);

void calibrateDrivetrain() {
    wait(200, msec);
    Brain.Screen.print("Calibrating");
    Brain.Screen.newLine();
    Brain.Screen.print("Inertial");
    BrainInertial.calibrate();
    while (BrainInertial.isCalibrating()) {
        wait(25, msec);
    }

    // Clears the screen and returns the cursor to row 1, column 1.
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
}

bool ifTaskPaused = true;

double leftVel = 0;
double rightVel = 0;

double Target = 0;
const double kP = 0.13;

double calculate(double target, double start) {
    double result = target - start;
    return result * kP;
}

int control() {
    while(true) {
        if (!ifTaskPaused) {
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1, 1);
            // Brain.Screen.print("in task");

            leftVel = calculate(Target, LeftDriveSmart.position(degrees) / 360 * 2 * 200);
            rightVel = calculate(Target, RightDriveSmart.position(degrees) / 360 * 2 * 200);
            LeftDriveSmart.setVelocity(leftVel, percent);
            RightDriveSmart.setVelocity(rightVel, percent);

            LeftDriveSmart.spin(forward);
            RightDriveSmart.spin(forward);

            wait(10, msec);

            Brain.Screen.print("%lf\n", leftVel);
            printf("%lf\n", LeftDriveSmart.position(degrees));
            printf("%lf\n\n\n\n", Target);
        } else {
            LeftDriveSmart.stop();
            RightDriveSmart.stop();

            LeftDriveSmart.setVelocity(75, percent);
            RightDriveSmart.setVelocity(75, percent);
        }
    }
}

task controlLoop(control);

void drive(double driveTarget) {
    LeftDriveSmart.setPosition(0, degrees);
    RightDriveSmart.setPosition(0, degrees);

    ifTaskPaused = false;
    driveTarget = driveTarget * 25.4;
    Target = driveTarget * 2;

    controlLoop.resume();
    wait(100, msec);

    while (!ifTaskPaused) {
        wait(5, msec);
        if (fabs(leftVel) <= 2 && fabs(rightVel) <= 2) {
            LeftDriveSmart.stop();
            RightDriveSmart.stop();

            ifTaskPaused = true;
        }
    }
    controlLoop.suspend();
    LeftDriveSmart.setVelocity(90, percent);
    RightDriveSmart.setVelocity(90, percent);
}

// void turndeg(int ang = 90, int Ts = 100, float x = -114) {
//     float pi = 3.14;
//     int w = 228;
//     int wheel_size = 200;
//     int gear_r = 2;

//     // printf("%f\n", ang);
//     // printf("%f\n", Ts);
//     // printf("%f\n", x);

//     float l = 2 * pi * (x + w) * (ang / 360);
//     float r = 2 * pi * x * (ang / 360);

//     float lSpeed = l > r ? Ts : l == 0 ? 0 : Ts * (r / l);
//     float rSpeed = r > l ? Ts : r == 0 ? 0 : Ts * (l / r);

//     l = l / wheel_size / gear_r * 360 * 2;
//     r = r / wheel_size / gear_r * 360 * 2;

//     // printf("%f\n", l);
//     // printf("%f\n", r);

//     LeftDriveSmart.setVelocity(lSpeed, percent);
//     RightDriveSmart.setVelocity(rSpeed, percent);

//     LeftDriveSmart.spinFor(forward, l, degrees, false);
//     RightDriveSmart.spinFor(forward, r, degrees);
// }
