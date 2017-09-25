import serial

ser = serial.Serial('/dev/ttyACM0', baudrate=9600)
print("connected to: " + ser.portstr)

while True:
    line = ser.readline()
    print(line)
ser.close()
