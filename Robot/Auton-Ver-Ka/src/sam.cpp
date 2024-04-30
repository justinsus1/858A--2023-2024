#include "vex.h"
#include "preAuton.h"
#include "driveFunc.h"

void dump(bool dump_correction, int type) {
    if(dump_correction == true) {
        Drivetrain.driveFor(300, mm);
        LeftDriveSmart.setVelocity(100, percent);
        RightDriveSmart.setVelocity(50, percent);
        LeftDriveSmart.spin(reverse);
        RightDriveSmart.spin(reverse);
        wait(2, seconds);
        LeftDriveSmart.stop();
        RightDriveSmart.stop();
    }
    if(type == 1) {
        Ratchet_Gear.spin(reverse);
        // Drivetrain.setTimeout(1, seconds);
        // Drivetrain.driveFor(10, mm);
        // Drivetrain.driveFor(-10, mm);
        // Drivetrain.driveFor(10, mm);
        // Drivetrain.driveFor(-10, mm);
        // Drivetrain.driveFor(10, mm);
        // Drivetrain.driveFor(-10, mm);
        wait(2, seconds);
        // Drivetrain.setTimeout(60, seconds);
    }
    if(type == 2) {
        Ratchet_Gear.setStopping(hold);
        pneumatic_system.extend(cylinder2);
        Ratchet_Gear.spin(reverse);
        wait(0.5, seconds);
        Ratchet_Gear.stop();
        // Drivetrain.driveFor(40, mm);
        // Drivetrain.driveFor(-40, mm);
        // Drivetrain.driveFor(40, mm);
        // Drivetrain.driveFor(-40, mm);
        // Drivetrain.driveFor(40, mm);
        wait(2, seconds);
    }
}

void wait_for_touchled() {
    touch_led.setColor(vex::green);
    while(!touch_led.pressing()){
        wait(10, msec);
    }
    touch_led.setColor(vex::red);
}

void setup() {
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
    touch_led.setColor(vex::blue);
    pneumatic_system.pumpOff();
    calibrateDrivetrain();
    pneumatic_system.pumpOn();
    Drivetrain.setStopping(brake);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.setTurnVelocity(300, percent);
	Drivetrain.setStopping(hold);   
    Ratchet_Gear.setMaxTorque(300, percent);
    Ratchet_Gear.setVelocity(300, percent);
    pneumatic_system.retract(cylinder2);
}

void curve(float radius, bool turnDirection,  int driveDirection, float angle, float speed) {
    double outerWheelDistance, innerWheelDistance;
    double outerMotorAngle, innerMotorAngle;
    double leftAngle, rightAngle;
    double innerSpeed, outerSpeed;
    outerWheelDistance = 2 * M_PI * (radius + WIDTH) * (angle / 360);
    innerWheelDistance = 2 * M_PI * radius * (angle / 360);
    outerMotorAngle = outerWheelDistance / WHEEL_SIZE / GEAR_RATIO * 360;
    innerMotorAngle = innerWheelDistance / WHEEL_SIZE / GEAR_RATIO * 360;
    outerSpeed = speed * driveDirection;
    innerSpeed = innerMotorAngle / outerMotorAngle * speed * driveDirection;
    leftAngle = turnDirection ? outerMotorAngle : innerMotorAngle;
    rightAngle = turnDirection ? innerMotorAngle : outerMotorAngle;
    LeftDriveSmart.setVelocity(turnDirection ? outerSpeed : innerSpeed, percent);
    RightDriveSmart.setVelocity(turnDirection ? innerSpeed : outerSpeed, percent);
    LeftDriveSmart.spinFor(driveDirection == 1 ? forward : reverse, leftAngle, degrees, false);
    RightDriveSmart.spinFor(driveDirection == 1 ? forward : reverse, rightAngle, degrees);
}

void Part1() {
    Ratchet_Gear.spin(forward);
    /////  Collect first 4  /////
    Drivetrain.driveFor(510, mm);
    /////  Collect center /////
    curve(120, true, 1, 70);
    Drivetrain.driveFor(350, mm);
    /////  Collect back strip /////
    curve(150, false, 1, 65);
    wait(0.5, seconds);
    Drivetrain.setDriveVelocity(75, percent);
    wait(0.5, seconds);
    Drivetrain.driveFor(170, mm);
    wait(0.5, seconds);
    curve(85, true, 1, 75);
    wait(0.5, seconds);
    Drivetrain.driveFor(250, mm);
    wait(0.5, seconds);
    Drivetrain.driveFor(reverse, 60, mm);
    wait(1, seconds);
    curve(85, true, -1, 120);
    Drivetrain.driveFor(75, mm);
    curve(150, false, 1, 30, 60);
    wait(500, msec);
    curve(200, false, 1, 60, 60);
    curve(500, false, 1, 30);
    wait(250, msec);
    Drivetrain.setStopping(coast);
    curve(800, false, 1, 20, 100);
    curve(1000, false, 1, 22, 50);
    wait(0.2, seconds);
    Drivetrain.driveFor(50, mm);
    wait(2, seconds);
    Drivetrain.setStopping(coast);
    Drivetrain.turnFor(15, degrees);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.drive(reverse);
    wait(3000, msec);
    Drivetrain.stop();
    dump(true, 2);
    Drivetrain.driveFor(100, mm);
    Drivetrain.driveFor(-100, mm);
    Drivetrain.stop();
    Drivetrain.setDriveVelocity(100, percent);
}

void Part2() {
    wait(250, msec);
    Ratchet_Gear.spin(forward);
    pneumatic_system.retract(cylinder2);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.driveFor(25, inches);
    wait(0.25, seconds);
    curve(95, false, 1, 55);
    wait(0.25, seconds);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.driveFor(35, inches);
    wait(0.25, seconds);
    curve(-114, false, 1, 50);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.drive(reverse);
    wait(3000, msec);
    Drivetrain.setStopping(coast);
    Drivetrain.stop();
    dump(false, 1);
    Drivetrain.stop();
    Drivetrain.setDriveVelocity(100, percent);
}

void Part3() {
    Ratchet_Gear.spin(forward);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.setStopping(coast);
    Drivetrain.driveFor(25, mm);
    curve(400, false, 1, 20, 100);
    Drivetrain.driveFor(680, mm);
    curve(200, false, 1, 57, 100);
    Drivetrain.setDriveVelocity(80, percent);
    Drivetrain.driveFor(350, mm);
    Drivetrain.setDriveVelocity(90, percent);
    Drivetrain.driveFor(-200, mm);
    curve(-114, true, 1, 40, 100);
    Drivetrain.setDriveVelocity(80, percent);
    Drivetrain.driveFor(600, mm);
    Drivetrain.turnFor(-85, degrees);
    LeftDriveSmart.setVelocity(300, percent);
    RightDriveSmart.setVelocity(300, percent);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.setDriveVelocity(300, percent);
    Drivetrain.drive(reverse);
    wait(3000, msec);
    Drivetrain.setStopping(coast);
    Drivetrain.stop();
    dump(false, 1);
    Drivetrain.stop();
    Drivetrain.setDriveVelocity(100, percent);
}

void end_of_match() {
    Drivetrain.setDriveVelocity(100, percent);
    Drivetrain.drive(forward);
    wait(2, seconds);
    Drivetrain.stop() ;
    Ratchet_Gear.stop();
    touch_led.setColor(vex::cyan);
    wait(0.5, seconds);
    touch_led.setColor(vex::cyan);
    wait(1, seconds);
    touch_led.setColor(vex::black);
    wait(0.5, seconds);
}

int sam_main() {
    setup();
    wait_for_touchled();
    Part1();
    Part2(); 
    wait_for_touchled();
    Part3();
    end_of_match();
    return 0;
}