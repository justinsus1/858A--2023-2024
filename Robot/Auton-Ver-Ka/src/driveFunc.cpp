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

#define WIDTH 228
#define GEAR_RATIO 2
#define WHEEL_SIZE 200

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

void turndeg(double angle = 90, int Ts = 100, double radius = 100, int driveDirection = 1, bool turnDirection = true) {
    // printf("hello from turndeg\n");
    double outerWheelDistance, innerWheelDistance;
    double outerMotorAngle, innerMotorAngle;
    double leftAngle, rightAngle;
    double innerSpeed, outerSpeed;

    // printf("ang: %d\n", angle);
    // printf("Ts: %d\n", Ts);
    // printf("radius: %lf\n", radius);
    // printf("driveDirection: %d\n", driveDirection);
    // printf("turnDirection: %d\n", turnDirection);

    outerWheelDistance = 2 * M_PI * (radius + WIDTH) * (angle / 360);
    innerWheelDistance = 2 * M_PI * radius * (angle / 360);

    outerMotorAngle = outerWheelDistance / WHEEL_SIZE / GEAR_RATIO * 360;
    innerMotorAngle = innerWheelDistance / WHEEL_SIZE / GEAR_RATIO * 360;

    outerSpeed = Ts * driveDirection;
    innerSpeed = innerMotorAngle / outerMotorAngle * Ts * driveDirection;

    leftAngle = turnDirection ? outerMotorAngle : innerMotorAngle;
    rightAngle = turnDirection ? innerMotorAngle : outerMotorAngle;

    LeftDriveSmart.setVelocity(turnDirection ? outerSpeed : innerSpeed, percent);
    RightDriveSmart.setVelocity(turnDirection ? innerSpeed : outerSpeed, percent);

    // printf("outerwheel: %lf\n", outerWheelDistance);
    // printf("innerwheel: %lf\n", innerWheelDistance);
    // printf("outerspeed: %lf\n", outerSpeed);
    // printf("innerspeed: %lf\n", innerSpeed);
    // printf("innerMotorAngle: %lf\n", innerMotorAngle);
    // printf("outerMotorAngle: %lf\n", outerMotorAngle);
    // printf("leftAngle: %lf\n", leftAngle);
    // printf("rightAngle: %lf\n", rightAngle);

    LeftDriveSmart.spinFor(forward, leftAngle, degrees, false);
    RightDriveSmart.spinFor(forward, rightAngle, degrees);
}
