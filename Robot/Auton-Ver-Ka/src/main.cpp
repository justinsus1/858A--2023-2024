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
    controller Controller1 = controller();

    controlLoop.suspend();
    calibrateDrivetrain();

    basketRoller.setVelocity(300, percent);
    basketRoller.setMaxTorque(300, percent);
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

    // touch();
    touchLed.setColor(green);

    basketRoller.stop();
    Drivetrain.stop();
}

void part1() {
    printf("driving\n");
    basketRoller.spin(forward);

    drive(16.5);

    turndeg(60, 70, 100, 1, true);

    drive(30);
    
    turndeg(25, 70, 150, 1, false);
    wait(500, msec);
    drive(12);
    wait(500, msec);

    turndeg(70, 80, 100, 1, true);
    drive(3);

    wait(500, msec);
    turndeg(180, 60, 50, -1, true);
    // To be continued
    // basketRoller.stop();
}

void part2() {
    drive(30);
    turndeg(60, 70, 200, 1, false);
    drive(27);

    LeftDriveSmart.setStopping(hold);
    LeftDriveSmart.spinFor(-50, degrees, false);

    wait(1, seconds);
    RightDriveSmart.spinFor(380, degrees);

    LeftDriveSmart.setTimeout(750, msec);
    RightDriveSmart.setTimeout(750, msec);

    drive(-20);

    LeftDriveSmart.setTimeout(100, seconds);
    RightDriveSmart.setTimeout(100, seconds);

    basketRoller.stop();
}

void part3() {
    basketRoller.spin(forward);

    turndeg(45, 100, 127, 1, false);
}

void touch() {
    while (!touchLed.pressing()) {
        wait(10, msec);
    }
}

int main() {
    printf("\n\nAuton:\n");
    setup();
    wait(1, seconds);
    // touch();
    // part1();
    // part2();
    part3();
    return 0;
}
