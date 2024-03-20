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
    printf("Part 3\n");
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
