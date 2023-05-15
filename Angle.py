import math

w = float(input("Track width mm: "))
wheel_size = float(input("Wheel size 200 for omni wheels: "))
x = float(input("Turning radius(negative half track width for on the spot): "))
gear_r = float(input("Gear ratio: "))
angle = float(input("Angle: "))

pi = math.pi

l = 2 * pi * (x + w) * (angle / 360)
r = 2 * pi * x * (angle / 360)

l = l / wheel_size / gear_r * 360
r = r / wheel_size / gear_r * 360

print(l * 1.33)
print(r * 1.33)
