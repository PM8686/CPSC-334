import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
import time
# import Adafruit_ADS1x15

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

# ADC = Adafruit_ADS1x15.ADS1115()
# ADC.read_adc(X_CHANNEL, gain=GAIN)

def main():
    prev_btn = -1
    prev_switch = -1
    start = time.time()
    while True: # Run forever
        print("x: ", GPIO.input(joypin_x), ", y: ", GPIO.input(joypin_y), ", sw: ", GPIO.input(joypin_sw))

        # button
        if GPIO.input(btn_pin) != prev_btn:
            # print(GPIO.input(btn_pin))
            if GPIO.input(btn_pin) == GPIO.HIGH:
                print("btn high")

            elif GPIO.input(btn_pin) == GPIO.LOW:
                print("btn low")
            prev_btn = GPIO.input(btn_pin)

        # switch
        if GPIO.input(switch_pin) != prev_switch:
            if GPIO.input(switch_pin) == GPIO.HIGH:
                print("on")

            elif GPIO.input(switch_pin) == GPIO.LOW:
                print("off")
                # return

            prev_switch = GPIO.input(switch_pin)


        time.sleep(.25)

main()