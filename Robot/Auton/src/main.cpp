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

    drive(17, 90);

    turndeg(60, 70, 100);

    drive(30, 90);
    
    turndeg(13, 70, 150, 1, false);
    wait(500, msec);
    drive(15);
    wait(500, msec);

    turndeg(82, 80, 100);
    wait(100, msec);

    wait(500, msec);
    turndeg(125, 60, 70, -1);

    drive(5, 90);
    drive(-17);

    turndeg(110, 100, 150, 1, false);

    drive(15);

    turndeg(20, 100, -114, 1, false);

    turndeg(50, 100, 150, 1, false);

    Drivetrain.drive(forward);
    wait(2, seconds);
    Drivetrain.stop();
    
    turndeg(-20);

    Drivetrain.drive(reverse);
    wait(2, seconds);
    Drivetrain.stop();

    LeftDriveSmart.stop();
    RightDriveSmart.stop();

    basketRoller.stop();
    pneumatics.extend(cylinder2);

    wait(2, seconds);
    basketRoller.spin(reverse);
    
    RightDriveSmart.spinFor(-600, degrees);
    wait(1, seconds);

    RightDriveSmart.stop();
    basketRoller.stop();
    drive(1);
    drive(-1);
}

void part2() {
    pneumatics.retract(cylinder2);
    basketRoller.spin(forward);

    drive(26);
    turndeg(70, 80, 200, 1, false);
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

void part3NoSupply() {
    drive(5);
    turndeg(67.5, 90, 25, 1, false);

    drive(50);
    turndeg(90);

    drive(41);
    turndeg(150, 100, -114, 1, false);

    drive(18);
    turndeg(40, 100, -114, 1, false);

    Drivetrain.drive(reverse);
    RightDriveSmart.spin(reverse);

    wait(3, seconds);
    Drivetrain.stop();

    basketRoller.spin(reverse);
    wait(500, msec);

    RightDriveSmart.stop();
    wait(500, msec);
    basketRoller.stop();
}

void park() {
    basketRoller.spin(forward);
    Drivetrain.drive(forward);
}

int main() {
    printf("\n\nAuton:\n");
    printf("Compilation date: %s %s\n", __TIME__, __DATE__);

    setup();
    // touch();

    // part1();
    // part2();
    part3NoSupply();
    park();
    return 0;
}
