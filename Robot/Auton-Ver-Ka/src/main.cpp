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
    
    turndeg(25, 70, 150, 1, false);
    wait(500, msec);
    drive(12);
    wait(500, msec);

    turndeg(70, 80, 100);
    drive(3);

    wait(500, msec);
    turndeg(120, 60, 50, -1);

    turndeg(120, 100, 100, 1, false);

    drive(3);

    turndeg(30, 100, -114, 1, false);

    Drivetrain.setTimeout(1, seconds);
    Drivetrain.driveFor(reverse, 10, inches);

    basketRoller.stop();
    pneumatics.extend(cylinder1);
    wait(2, seconds);
}

void part2() {
    pneumatics.retract(cylinder1);
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

}

int main() {
    printf("\n\nAuton:\n");

    setup();

    pneumatics.pumpOff();
    wait(1, seconds);
    touch();

    part1();
    // part2();
    // part3();

    return 0;
}
