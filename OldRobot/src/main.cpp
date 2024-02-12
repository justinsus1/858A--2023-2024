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
motor B_RMotorB = motor(PORT6, true);
motor_group B_R = motor_group(B_RMotorA, B_RMotorB);

touchled touchLed = touchled(PORT1);

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

// Define Global Variables
bool ifTaskPaused = true;

double leftVel = 0;
double rightVel = 0;

double Target = 0;
const double kP = 0.4;

// Define Prototype functions
double calculate(double target, double start);
void drive(double target);
void turndeg(float ang);
int control();
void setup();
void Part1();
void Part2();
void Part3();
void touch();

task controlLoop(control);

// Calculate function to get Velocity
double calculate(double target, double start) {
    double result = target - start;
    return result * kP;
}

// Control loop to implement P
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

// Function to use the Control loop
void drive(double driveTarget) {
    LeftDriveSmart.setPosition(0, degrees);
    RightDriveSmart.setPosition(0, degrees);
    ifTaskPaused = false;
    driveTarget = driveTarget * 24.5;
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
    LeftDriveSmart.setVelocity(90, percent);
    RightDriveSmart.setVelocity(90, percent);
    LeftDriveSmart.setMaxTorque(100, percent);
    RightDriveSmart.setMaxTorque(100, percent);
    LeftDriveSmart.setStopping(hold);
    RightDriveSmart.setStopping(hold);
    Drivetrain.setDriveVelocity(90, percent);
    Drivetrain.setStopping(hold);
    Drivetrain.drive(reverse);
    Brain.Screen.print("hello");
    B_R.spin(forward);
    touch();
    B_R.stop();
}

void part1() {
    B_R.spin(forward);
    drive(32);
    LeftDriveSmart.setVelocity(65, percent);
    RightDriveSmart.setVelocity(100, percent);
    LeftDriveSmart.spinFor(-150, degrees, false);
    RightDriveSmart.spinFor(-600, degrees);

    drive(5);
    LeftDriveSmart.spinFor(-180, degrees);
    // wait(100, msec);

    RightDriveSmart.setVelocity(75, percent);
    LeftDriveSmart.setVelocity(35, percent);
    LeftDriveSmart.spinFor(600, degrees, false);
    RightDriveSmart.spinFor(1200, degrees);
    RightDriveSmart.setVelocity(90, percent);
    LeftDriveSmart.setVelocity(90, percent);
    turndeg(32);
    turndeg(0 - BrainInertial.rotation());
    RightDriveSmart.setVelocity(70, percent);
    LeftDriveSmart.setVelocity(70, percent);
    Drivetrain.drive(forward);
    wait(2, seconds);
    Drivetrain.stop();
    RightDriveSmart.setVelocity(90, percent);
    LeftDriveSmart.setVelocity(90, percent);
    drive(-6);
    turndeg(75);
    drive(25);
    turndeg(30);
    drive(4);
    turndeg(220);
    drive(3);
    LeftDriveSmart.setVelocity(65, percent);
    RightDriveSmart.setVelocity(65, percent);
    turndeg(25);
    Brain.Screen.print("Hello");
    drive(60);
    LeftDriveSmart.setVelocity(90, percent);
    RightDriveSmart.setVelocity(90, percent);
    turndeg(-42.5);
    drive(1);
    turndeg(-52.5);
    drive(24);
    turndeg(-60);
    // drive(-7);
    // turndeg(-79);
    LeftDriveSmart.spin(forward);
    Drivetrain.drive(reverse);
    wait(3500, msec);
    Drivetrain.stop();
    wait(1, seconds);
    LeftDriveSmart.stop();
    B_R.setTimeout(2, seconds);
    B_R.spinFor(-450, degrees);
    wait(2, seconds);
    B_R.spinFor(600, degrees);
}

void part2() {
    B_R.spin(forward);
    drive(2);
    turndeg(-50);
    drive(25);
    // turndeg(40); 
    turndeg(29);
    drive(23.5);
    turndeg(155);
    wait(500, msec);
    drive(13.5);
    B_R.stop();
    drive(5);
    turndeg(80);
    B_R.spin(forward);
    Drivetrain.drive(reverse);
    wait(1, seconds);
    Drivetrain.stop();
    LeftDriveSmart.spin(reverse);
    wait(500, msec);
    LeftDriveSmart.stop();
    B_R.stop();
    B_R.spinFor(-1250, degrees);
    wait(2, seconds);
    B_R.spinFor(1500, degrees);

    // Uncomplete code used for practice do not use

    // B_R.spin(forward);
    // Drivetrain.setDriveVelocity(80, percent);
    // drive(31.5);
    // Drivetrain.setDriveVelocity(100, percent);
    // drive(-23.5);
    // turndeg(-45);
    // wait(500, msec);
    // drive(25);
    // turndeg(75);
    // Drivetrain.drive(reverse);
    // wait(1, seconds);
    // Drivetrain.stop();
    // RightDriveSmart.spinFor(45, degrees);
    // LeftDriveSmart.spin(reverse);
    // wait(1000, msec);
    // LeftDriveSmart.stop();
    // B_R.stop();
    // B_R.spinFor(-1250, degrees);
    // wait(2, seconds);
    // B_R.spinFor(1500, degrees);
}

void part3() {
    B_R.spin(forward);
    Drivetrain.setDriveVelocity(80, percent);
    drive(31.5);
    Drivetrain.setDriveVelocity(100, percent);
    drive(-23.5);
    turndeg(45);
    wait(500, msec);
    drive(25);
    turndeg(-75);
    Drivetrain.drive(reverse);
    wait(1, seconds);
    Drivetrain.stop();
    LeftDriveSmart.spinFor(45, degrees);
    RightDriveSmart.spin(reverse);
    wait(1000, msec);
    RightDriveSmart.stop();
    B_R.stop();
    B_R.spinFor(-1250, degrees);
    wait(2, seconds);
    Drivetrain.drive(forward);
}

void touch() {
    while (not(touchLed.pressing())) {
    }
}

int main() {                                             
    setup();
    wait(1, seconds);
    touch();
    part1();
    part2();
    touch();
    part3();
    return 0; 
}
