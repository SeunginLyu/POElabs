import serial

ser = serial.Serial('/dev/ttyACM1', baudrate=9600, timeout=20)

f = open('output.csv', 'w+')
while True:
    line = ser.readline()
    line = line.decode("utf-8")
    print(line)
    if line:  # If it isn't a blank line
            f.write(line)
ser.close()
