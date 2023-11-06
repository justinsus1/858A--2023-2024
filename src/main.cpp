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

#pragma endregion VEXcode Generated Robot Configuration
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       justin_sus1                                               */
/*    Created:      10/23/2023, 7:48:46 PM                                    */
/*    Description:  IQ2 project                                               */
/*                  -                                                          */
/*---------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
// vex::brain       Brain;

// define your global instances of motors and other devices here

motor leftMotorA = motor(PORT3, 2.5, true);
motor leftMotorB = motor(PORT2, 2.5, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT8, 2.5, false);
motor rightMotorB = motor(PORT9, 2.5, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, BrainInertial, 200);

motor B_RMotorA = motor(PORT4, false);
motor B_RMotorB = motor(PORT5, true);
motor_group B_R = motor_group(B_RMotorA, B_RMotorB);

// touchled touchdakid = touchled(PORT6);

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
const double kP = 0.4;

double calculate(double target, double start);
void die(double target);
void turndeg(float ang);
int control();
void setup();
void Part1();
void Part2();
void Part3();

task controlLoop(control);

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
            printf("%lf\n", Target);
        } else {
            LeftDriveSmart.stop();
            RightDriveSmart.stop();
            LeftDriveSmart.setVelocity(75, percent);
            RightDriveSmart.setVelocity(75, percent);
        }
    }
}

void die(double diveTarget) {
    LeftDriveSmart.setPosition(0, degrees);
    RightDriveSmart.setPosition(0, degrees);
    ifTaskPaused = false;
    diveTarget = diveTarget * 24.5;
    Target = diveTarget * 2;
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
    LeftDriveSmart.setVelocity(100, percent);
    RightDriveSmart.setVelocity(100, percent);
}

void turndeg(float ang) {
    float pi = 3.14;
    int w = 225;
    int wheel_size = 200;
    float x = -112.5;
    int gear_r = 2;
    float l = 2 * pi * (x + w) * (ang / 360);
    float r = 2 * pi * x * (ang / 360);
    l = l / wheel_size / gear_r * 360 * 2;
    r = r / wheel_size / gear_r * 360 * 2;
    LeftDriveSmart.spinFor(forward, l, degrees, false);
    RightDriveSmart.spinFor(forward, r, degrees);
}

void setup() {
    controlLoop.suspend();  
    calibrateDrivetrain();
    B_R.setVelocity(100, percent);
    B_R.setMaxTorque(100, percent);
    B_R.setStopping(brake);
    LeftDriveSmart.setVelocity(100, percent);
    RightDriveSmart.setVelocity(100, percent);
    LeftDriveSmart.setMaxTorque(75, percent);
    RightDriveSmart.setMaxTorque(75, percent);
    LeftDriveSmart.setStopping(hold);
    RightDriveSmart.setStopping(hold);
    Drivetrain.setDriveVelocity(75, percent);
    Drivetrain.setStopping(hold);
    Drivetrain.drive(reverse);
    Brain.Screen.print("hello");
}

void part1() {
    B_R.spin(forward);
    die(32);

    LeftDriveSmart.setVelocity(65, percent);
    RightDriveSmart.setVelocity(100, percent);
    LeftDriveSmart.spinFor(-150, degrees, false);
    RightDriveSmart.spinFor(-600, degrees);

    LeftDriveSmart.setVelocity(25, percent);
    LeftDriveSmart.spinFor(200, degrees, false);
    RightDriveSmart.spinFor(1200, degrees);
    // die(15);
    // turndeg(-128);
    // die(7.5);
    // turndeg(42);
    // die(20);
    // turndeg(85);
    // Drivetrain.drive(forward);
    // wait(2, seconds);
    // Drivetrain.stop();
    // B_R.stop();
    // Drivetrain.drive(reverse);
    // wait(3, seconds);
    // Drivetrain.stop();
}

void part2() {
    turndeg(-33);
    die(-16);
    turndeg(-96);
    die(30);
    turndeg(180);
    Drivetrain.drive(reverse);
    wait(3, seconds);
    Drivetrain.stop();
}

int main() {                                             
    setup();
    part1();
    return 0; 
}
