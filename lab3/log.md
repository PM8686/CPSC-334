Task 1: button, 3 states
- using python gpio library
- https://raspberrypihq.com/use-a-push-button-with-raspberry-pi-gpio/
- two lower pins, one to GND, the other to resistor to Vdd, across either pin to the digital read.

Task 2: switch, 3 states
- blue wire to GND
- yellow wire to resistor to GND
- use the resistor to red wire so that one system shorting it does not short everywhere.
- want basic state to have 0 current

Task 3: joy stick
- VRX and VRY to any GPIO, sw is just a switch
- just use like a requglar swtich or button
- resting state stuck at x = y = 1
- pull_up_down=GPIO.PUD_UP for sw to work (as oppposed to pull_up_down=GPIO.PUD_DOWN)

