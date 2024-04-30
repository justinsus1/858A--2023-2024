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

motor Ratchet_GearA = motor(PORT8, false);
motor Ratchet_GearB = motor(PORT12, true);
motor_group Ratchet_Gear = motor_group(Ratchet_GearA, Ratchet_GearB);

touchled touch_led = touchled(PORT6);

pneumatic pneumatic_system = pneumatic(PORT5);

void touch() {
    while (!touch_led.pressing()) {
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
    
    if (!Ratchet_GearA.installed()) {
        Brain.Screen.print("BRM in PORT8 unplugged");
        printf("BRM in PORT8 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!Ratchet_GearB.installed()) {
        Brain.Screen.print("BRM in PORT12 unplugged");
        printf("BRM in PORT12 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!touch_led.installed()) {
        Brain.Screen.print("TL in PORT6 unplugged");
        printf("TL in PORT6 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }
    
    if (!pneumatic_system.installed()) {
        Brain.Screen.print("Pneumatics in PORT5 unplugged");
        printf("Pneumatics in PORT5 unplugged\n");
        Brain.playSound(alarm);
        wait(30, seconds);
    }

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
}

void setup() {
    checkDevice();

    printf("Battery level: %d%%\n", Brain.Battery.capacity(percent));
    printf("Battery voltage: %.2lfV\n", Brain.Battery.voltage(volt));
    printf("Battery level before rounding: %.2lf%%\n", Brain.Battery.voltage(volt) / 0.084);

    controlLoop.suspend();
    pneumatic_system.pumpOff();
    calibrateDrivetrain();

    pneumatic_system.pumpOn();
    pneumatic_system.retract(cylinder2);

    Ratchet_Gear.setVelocity(300, percent);
    Ratchet_Gear.setMaxTorque(300, percent);
    Ratchet_Gear.setStopping(hold);

    LeftDriveSmart.setVelocity(300, percent);
    RightDriveSmart.setVelocity(300, percent);

    LeftDriveSmart.setMaxTorque(300, percent);
    RightDriveSmart.setMaxTorque(300, percent);

    LeftDriveSmart.setStopping(hold);
    RightDriveSmart.setStopping(hold);

    Drivetrain.setDriveVelocity(10, percent);
    Drivetrain.setStopping(hold);
    // Drivetrain.drive(reverse);

    touch_led.setColor(red);

    Ratchet_Gear.spin(forward);

    // touch();
    touch_led.setColor(green);

    Ratchet_Gear.stop();
    Drivetrain.stop();
    Drivetrain.setDriveVelocity(90, percent);

    wait(5, seconds);
    pneumatic_system.pumpOff();
}