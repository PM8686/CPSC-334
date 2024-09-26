import serial

while True:
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.1)
    line = ser.readline()   # read a '\n' terminated line
    print(line)