#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vex.h"
#include "driveFunc.h"
#include "preAuton.h"

using namespace vex;

void part1();
void part2();
void part3();

void part1() {
    printf("Part 1\n");
    basketRoller.spin(forward);

    drive(16.5);

    turndeg(60, 70, 100);

    drive(30);
    
    turndeg(15, 70, 150, 1, false);
    wait(500, msec);
    drive(15);
    wait(500, msec);

    turndeg(80, 80, 100);
    // drive(5);
    wait(100, msec);

    wait(500, msec);
    turndeg(125, 60, 70, -1);

    drive(5);
    drive(-20);

    turndeg(110, 100, 150, 1, false);

    drive(15);

    turndeg(20, 100, -114, 1, false);

    turndeg(50, 100, 150, 1, false);

    Drivetrain.drive(forward);
    wait(2, seconds);

    Drivetrain.setTimeout(1, seconds);
    Drivetrain.driveFor(reverse, 13, inches);

    LeftDriveSmart.stop();
    RightDriveSmart.stop();
    basketRoller.stop();
    pneumatics.retract(cylinder2);
    wait(2, seconds);
    basketRoller.spin(reverse);
    wait(1, seconds);
    basketRoller.stop();
    drive(1);
    drive(-1);
}

void part2() {
    pneumatics.extend(cylinder2);
    basketRoller.spin(forward);

    drive(30);
    turndeg(60, 70, 200, 1, false);
    drive(27);

    LeftDriveSmart.setStopping(hold);
    LeftDriveSmart.spinFor(-50, degrees, false);

    wait(1, seconds);
    RightDriveSmart.spinFor(380, degrees);

    Drivetrain.setTimeout(750, msec);
    Drivetrain.driveFor(reverse, 20, inches);

    LeftDriveSmart.setTimeout(100, seconds);
    RightDriveSmart.setTimeout(100, seconds);

    basketRoller.stop();
    basketRoller.spinFor(-640, degrees);
    wait(2, seconds);
}

void part3() {
    basketRoller.spin(forward);
    drive(37.5);

    turndeg(90, 100, 100, 1, false)
    

    // oops this is non supply zone
    // drive(5);
    // turndeg(67.5, 90, 25, 1, false);

    // drive(50);
    // turndeg(90);
}

int main() {
    printf("\n\nAuton:\n");

    setup();

    wait(1, seconds);
    // touch();
    pneumatics.pumpOff();

    // part1();
    // part2();
    part3();

    return 0;
}
