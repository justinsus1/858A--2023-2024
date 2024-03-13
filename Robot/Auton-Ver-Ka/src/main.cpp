#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vex.h"
#include "driveFunc.h"

using namespace vex;

void setup();
void Part1();
void Part2();
void Part3();
void touch();

void setup() {
    controlLoop.suspend();
    calibrateDrivetrain();

    basketRoller.setVelocity(100, percent);
    basketRoller.setMaxTorque(100, percent);
    basketRoller.setStopping(brake);

    LeftDriveSmart.setVelocity(100, percent);
    RightDriveSmart.setVelocity(100, percent);

    LeftDriveSmart.setMaxTorque(100, percent);
    RightDriveSmart.setMaxTorque(100, percent);

    LeftDriveSmart.setStopping(hold);
    RightDriveSmart.setStopping(hold);

    Drivetrain.setDriveVelocity(90, percent);
    Drivetrain.setStopping(hold);
    // Drivetrain.drive(reverse);

    touchLed.setColor(red);

    Brain.Screen.print("hello");
    basketRoller.spin(forward);

    touch();
    touchLed.setColor(green);

    basketRoller.stop();
    Drivetrain.stop();
}

void part1() {
    basketRoller.spin(forward);

    LeftDriveSmart.setVelocity(90, percent);
    RightDriveSmart.setVelocity(90, percent);

    drive(16.5);
    LeftDriveSmart.setVelocity(100, percent);
    RightDriveSmart.setVelocity(100, percent);
    turndeg(60, 100, 300, 1, true);

    wait(3, seconds);
    drive(16);

    Drivetrain.turnToHeading(90, degrees);

    drive(4);
    // turndeg(70);
    drive(6);
    
    // turndeg(10);
    drive(23);
    // To be continued
    basketRoller.stop();
}

void part2() {
    basketRoller.spin(forward);

    drive(44);
    LeftDriveSmart.setVelocity(35, percent);
    RightDriveSmart.setVelocity(75, percent);

    LeftDriveSmart.spinFor(600, degrees, false);
    RightDriveSmart.spinFor(1200, degrees);

    LeftDriveSmart.setVelocity(100, percent);
    RightDriveSmart.setVelocity(100, percent);

    drive(36);
    // turndeg(45);
    // drive()
}

void part3() {
    basketRoller.spin(forward);

    Drivetrain.setDriveVelocity(80, percent);
    drive(31.5);
    Drivetrain.setDriveVelocity(90, percent);

    drive(-23.5);
    // turndeg(45);
    wait(500, msec);
    drive(25);
    // turndeg(-75);

    Drivetrain.drive(reverse);
    wait(1, seconds);
    Drivetrain.stop();

    LeftDriveSmart.spinFor(75, degrees);
    RightDriveSmart.spin(reverse);

    wait(200, msec);
    RightDriveSmart.stop();
    basketRoller.stop();
    basketRoller.spinFor(-1250, degrees);
    wait(800, msec);
    Drivetrain.drive(forward);
}

void touch() {
    while (!touchLed.pressing()) {
    }
}

int main() {
    
    setup();
    wait(1, seconds);
    touch();
    part1();
    // part2();
    // touch();
    // part3();
    return 0;
}
