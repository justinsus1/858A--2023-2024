#ifndef XDRIVE_HPP_
#define XDRIVE_HPP_

#ifndef VEX_H_
#define VEX_H_
#include "vex.h"
#endif

#ifndef IQ2_CPP_H_
#define IQ2_CPP_H_
#include "iq2_cpp.h"
#endif

#ifndef MATH_H_
#define MATH_H_
#include <math.h>
#endif

#ifndef SRA_UTILS_HPP_
#define SRA_UTILS_HPP_
#include "sra_utils.hpp"
#endif

#define WHEEL_CIRUM 200

namespace sra {

enum TurnDir {
  clockwise = 1,
  anticlockwise = -1
};

enum ControlScheme {
  field = 1,
  robot = 0
};

enum GyroInertial {
  gyroSensor = 1,
  inertialSensor = 0
};

struct Point {
    float x, y, theta;
};

void printfFloat(float decimal, bool newline = false) {
    printf("%d.%d", static_cast<int>(decimal), abs(static_cast<int>(decimal * 100) % 100));
    printf(newline ? "\n" : "");
}

float degToRad(float angle) {
    return angle * M_PI / 180;
}

float max(float a, float b, float c) {
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

class xDrive {
  private:
    vex::motor Motors[4];
    vex::gyro Gyro = NULL;
    vex::inertial Inertia;
    vex::controller IQ_Controller;

    void turnMotorsFor(float distances[4], float speed, bool debug = false) {
      bool finished = false;

      for (int i = 0; i <= 3; i++) {
        if (static_cast<int>(distances[i]) == 0) {
          Motors[i].setVelocity(0, vex::percent);
          if (debug) {
            printf("Motor %d not moving\n", i + 1);
          }
        } else {
          Motors[i].spin(vex::forward);
          Motors[i].setVelocity(speed, vex::percent);
          Motors[i].spinFor(vex::forward, distances[i], vex::degrees, false);
          if (debug) {
            printf("Motor %d turning %d degrees \n", i + 1, static_cast<int>(distances[i]));
          }
        }
      }
      wait(200, vex::msec);

      while (!finished) {
        finished = true;

        for (int i = 0; i <= 3; i++) {
          if (fabs(Motors[i].velocity(vex::percent)) > 3 ) {
            finished = false;
          }
        }
        wait(10, vex::msec);
      }
      printF("\n")
    }
    void resetMotors(float speed) {
      for (int i = 0; i <= 3; i++) {
        Motors[i].setBrake(vex::brakeType::hold);
        Motors[i].setVelocity(speed, vex::percent);
        Motors[i].spin(vex::forward);
      }
    }
};

} // Namespace sra

#endif // XDRIVE_HPP_
