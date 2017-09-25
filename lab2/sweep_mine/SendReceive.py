import serial
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d

def convert_to_cartesian(r, theta, phi):
    theta = theta / 180 * np.pi
    phi = phi / 180 * np.pi
    r = 15 + (560 - r) / 10 # calibrated for distances over 15 cm
    x = r * np.sin(theta) * np.cos(phi)
    y = r * np.cos(theta) * np.cos(phi)
    z = r * np.sin(phi)
    return iter([x,y,z])

def parse_line(line):
    line = line.strip('b\'\\nr')
    foo = tuple(line.split(','))
    return foo

ser = serial.Serial('/dev/ttyACM0', baudrate=9600, timeout=3)
print("connected to: " + ser.portstr)


points = []

while True:
    line = ser.readline()
    print(line)
    coordinates = parse_line(line)
    points.append(coordinates)
    if coordinates[1] == 99 && coordinates[2] == 0:
        break
ser.close()

fig = plt.figure()
ax = fig.add_subplot(1,1,1)
ax = fig.gca(projection='3d')

for r, theta, phi in foo:
    data = convert_to_cartesian(r, theta, phi)
    x, y, z = data
    ax.scatter(x, y, z, alpha=0.8, edgecolors='none')

plt.show()