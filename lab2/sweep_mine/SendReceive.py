import serial
import numpy as np
import matplotlib.pyplot as plt
import csv
from mpl_toolkits.mplot3d import axes3d


def convert_to_cartesian(r, theta, phi):
    theta = theta * (np.pi / 180)
    phi = phi * (np.pi / 180)
    r = 15 + (560 - r) / 10  # calibrated for distances over 15 cm
    x = r * np.cos(theta) * np.sin(phi)
    y = r * np.sin(theta) * np.sin(phi)
    z = r * np.cos(phi)
    return iter([x, y, z])


def parse_line(line):

    line = line.decode('utf8').strip("b\'\n\r")
    coordinates = []
    for coordinate in line.split(','):
        coordinates.append(int(coordinate))
    coordinates = (coordinates[0], coordinates[1], coordinates[2])
    return coordinates


ser = serial.Serial('/dev/ttyACM0', baudrate=9600, timeout=20)
print("connected to: " + ser.portstr)

points = []
while True:
    line = ser.readline()
    print(line)
    coordinates = parse_line(line)
    print(coordinates)
    points.append(coordinates)
    if coordinates[1] == 49 and coordinates[2] == 0:
        break

ser.close()
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1, projection='3d')
result = []
for r, theta, phi in points:
        data = convert_to_cartesian(r, theta, phi)
        x, y, z = data
        result.append((x, y, z))
        ax.scatter(x, y, z, c='r', marker='o')

with open('sphericals4.csv', 'w') as f:
    writer = csv.writer(f, delimiter=';', lineterminator='\n')
    writer.writerows(points)

with open('result4.csv', 'w') as f:
    writer = csv.writer(f, delimiter=';', lineterminator='\n')
    writer.writerows(result)


ax.set_xlabel('X (cm)')
ax.set_ylabel('Y (cm)')
ax.set_zlabel('Z (cm)')
plt.show()
