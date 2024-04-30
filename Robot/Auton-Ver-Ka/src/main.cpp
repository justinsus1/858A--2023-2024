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
void part3Supply();

void part1() {
    printf("Part 1\n");
    Ratchet_Gear.spin(forward);

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
    Drivetrain.stop();

    LeftDriveSmart.stop();
    RightDriveSmart.stop();

    Ratchet_Gear.stop();
    pneumatic_system.extend(cylinder2);

    wait(500, msec);
    Ratchet_Gear.spinFor(reverse, 200, degrees);
    
    Drivetrain.driveFor(1.1, inches);
    Drivetrain.driveFor(-1, inches);

    RightDriveSmart.stop();
    Ratchet_Gear.stop();
}

void part2() {
    pneumatic_system.retract(cylinder2);
    Ratchet_Gear.spin(forward);

    drive(25);
    turndeg(80, 80, 200, 1, false);
    drive(27);

    LeftDriveSmart.setStopping(hold);
    LeftDriveSmart.spinFor(-50, degrees, false);

    wait(1, seconds);
    RightDriveSmart.spinFor(380, degrees);

    Drivetrain.setTimeout(750, msec);
    Drivetrain.driveFor(reverse, 20, inches);

    LeftDriveSmart.setTimeout(100, seconds);
    RightDriveSmart.setTimeout(100, seconds);

    Ratchet_Gear.stop();
    Ratchet_Gear.spinFor(-650, degrees);
    wait(500, msec);
    drive(1, 300);
    drive(-1, 300);
}

void part3Supply() {
    Ratchet_Gear.spin(forward);
    drive(8);
    turndeg(42, 100, 80, 1, false);
    drive(36, 300);

    turndeg(58, 80, 150, 1, false);

    drive(48, 300);

    turndeg(75);

    // next to the supply zone
    Drivetrain.setDriveVelocity(60, percent);
    Drivetrain.drive(forward);
    wait(3, seconds);
    Drivetrain.stop();

    Drivetrain.driveFor(reverse, 8, inches);
    // wait(200, msec);

    turndeg(30, 100, -80, 1, false);
    Drivetrain.driveFor(forward, 4, inches);
    wait(500, msec);
    turndeg(30, 100, -80, 1, true);

    // basketRoller.spin(reverse);
    Ratchet_Gear.setStopping(coast);
    
    Drivetrain.drive(reverse);
    wait(1300, msec);
    Drivetrain.stop();
    
    turndeg(70, 90, -114, 1, true);
    drive(32);

    turndeg(210);
    Drivetrain.setDriveVelocity(80, percent);
    Drivetrain.drive(reverse);
    wait(1, seconds);
    Drivetrain.stop();

    RightDriveSmart.spin(reverse);
    wait(200, msec);
    RightDriveSmart.stop();

    Ratchet_Gear.spinFor(-660, degrees);
    drive(1, 300);
    drive(-1, 300);

    Drivetrain.drive(forward);
    wait(3, seconds);
    Drivetrain.stop();
}

int justin_main() {
    printf("\n\nAuton:\n");
    printf("Compilation date: %s %s\n", __TIME__, __DATE__);

    setup();
    touch();

    part1();
    part2();
    part3Supply();

    return 0;
}

int main() {
    // justin_main();
    // sam_main();
    
    return 0;
}