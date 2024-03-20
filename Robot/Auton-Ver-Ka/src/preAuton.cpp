#include "vex.h"
#include "driveFunc.h"

using namespace vex;

brain Brain;
inertial BrainInertial = inertial();

motor leftMotorA = motor(PORT4, 2.5, true);
motor leftMotorB = motor(PORT2, 2.5, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

motor rightMotorA = motor(PORT10, 2.5, false);
motor rightMotorB = motor(PORT11, 2.5, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, BrainInertial, 200);

motor basketRollerMotorA = motor(PORT8, false);
motor basketRollerMotorB = motor(PORT12, true);
motor_group basketRoller = motor_group(basketRollerMotorA, basketRollerMotorB);

touchled touchLed = touchled(PORT6);

pneumatic pneumatics = pneumatic(PORT5);

void touch() {
    while (!touchLed.pressing()) {
        wait(10, msec);
    }
}

void checkDevice() {
    if (!leftMotorA.installed()) {
        Brain.Screen.print("LDM in PORT4 unplugged");
        printf("LDM in PORT4 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!leftMotorB.installed()) {
        Brain.Screen.print("LDM in PORT2 unplugged");
        printf("LDM in PORT2 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!rightMotorA.installed()) {
        Brain.Screen.print("RDM in PORT10 unplugged");
        printf("RDM in PORT10 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!rightMotorB.installed()) {
        Brain.Screen.print("RDM in PORT11 unplugged");
        printf("RDM in PORT11 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!basketRollerMotorA.installed()) {
        Brain.Screen.print("BRM in PORT8 unplugged");
        printf("BRM in PORT8 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!basketRollerMotorB.installed()) {
        Brain.Screen.print("BRM in PORT12 unplugged");
        printf("BRM in PORT12 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!touchLed.installed()) {
        Brain.Screen.print("TL in PORT6 unplugged");
        printf("TL in PORT6 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!pneumatics.installed()) {
        Brain.Screen.print("Pneumatics in PORT5 unplugged");
        printf("Pneumatics in PORT5 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
}

void setup() {
    printf("\n\nAuton:\n");
    checkDevice();

    printf("%d\n", Brain.Battery.capacity(percent));

    controlLoop.suspend();
    pneumatics.pumpOff();
    calibrateDrivetrain();

    pneumatics.pumpOn();
    pneumatics.retract(cylinder1);

    basketRoller.setVelocity(300, percent);
    basketRoller.setMaxTorque(300, percent);
    basketRoller.setStopping(hold);

    LeftDriveSmart.setVelocity(300, percent);
    RightDriveSmart.setVelocity(300, percent);

    LeftDriveSmart.setMaxTorque(300, percent);
    RightDriveSmart.setMaxTorque(300, percent);

    LeftDriveSmart.setStopping(hold);
    RightDriveSmart.setStopping(hold);

    Drivetrain.setDriveVelocity(10, percent);
    Drivetrain.setStopping(hold);
    // Drivetrain.drive(reverse);

    touchLed.setColor(red);

    basketRoller.spin(forward);

    // touch();
    touchLed.setColor(green);

    basketRoller.stop();
    Drivetrain.stop();
    Drivetrain.setDriveVelocity(90, percent);
}