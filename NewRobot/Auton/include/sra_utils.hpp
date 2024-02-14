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
