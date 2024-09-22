import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
import time

btn_pin = 10
switch_pin = 8
joypin_x = 12
joypin_y = 11
joypin_sw = 13
GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(btn_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP) 
GPIO.setup(switch_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP) 
GPIO.setup(joypin_x, GPIO.IN, pull_up_down=GPIO.PUD_UP) 
GPIO.setup(joypin_y, GPIO.IN, pull_up_down=GPIO.PUD_UP) 
GPIO.setup(joypin_sw, GPIO.IN, pull_up_down=GPIO.PUD_UP) 

# Define modes
MODE_ONE = 0
MODE_TWO = 1
MODE_THREE = 2
MODE_OFF = 3
mode = MODE_ONE

def main():
    prev_btn = -1
    prev_switch = -1

    while True:
        # Read joystick values
        x = GPIO.input(joypin_x)
        y = GPIO.input(joypin_y)
        sw = GPIO.input(joypin_sw)

        # Print joystick values
        # print(f"x: {x}, y: {y}, sw: {sw}")

        # Check button press
        if GPIO.input(btn_pin) != prev_btn:
            if GPIO.input(btn_pin) == GPIO.LOW:
                if mode == MODE_ONE:
                    if x == 0: print('Mode 1: a', end='')
                    else: print('Mode 1: b', end='')
                    if sw == 0: print('0', end='')
                    else: print('1', end='')
                    if y == 0: print('y', end='')
                    else: print('z')
                elif mode == MODE_TWO:
                    if x == 0: print('Mode 2: x is 0', end='')
                    else: print('Mode 2: x is 1', end='')
                    if sw == 0: print(' (switch is 0)', end='')
                    else: print(' (switch is 1)', end='')
                    if y == 0: print(' (y is 0)', end='')
                    else: print(' (y is 1)')
                elif mode == MODE_THREE:
                    if x == 0: print('Mode 3: Joystick left', end='')
                    else: print('Mode 3: Joystick right', end='')
                    if sw == 0: print(' (button pressed)', end='')
                    else: print(' (button released)', end='')
                    if y == 0: print(' (moving down)', end='')
                    else: print(' (moving up)')
                elif mode == MODE_OFF:
                    return  # Exit the program
            prev_btn = GPIO.input(btn_pin)

        # Check switch state
        if GPIO.input(switch_pin) != prev_switch:
            if GPIO.input(switch_pin) == GPIO.LOW:  # Switch is on
                mode = (mode + 1) % 4  # Cycle through modes
            prev_switch = GPIO.input(switch_pin)

        time.sleep(0.25)

main()