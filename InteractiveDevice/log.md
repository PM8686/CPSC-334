## Files:
- ESP32_game: arduino code for the ESP32
- game: past arduino code for the ESP32 (contains some old functions I want to refer to, used OLED)
- game_laptop.py: final game code
- log.md: the log
- task1.py: simple functions that test the switch, button and joystick functionality
- test.py: testing the game using just software (all hardware replaced with computer keys)

---------------------

## Task 1: 
Demonstrate 3 Modes of Operation with a Button, a Switch, a Joystick
- button
    - using python gpio library
    - https://raspberrypihq.com/use-a-push-button-with-raspberry-pi-gpio/
    - two lower pins, one to GND, the other to resistor to Vdd, across either pin to the digital read.

- switch
    - blue wire to GND
    - yellow wire to resistor to GND
    - use the resistor to red wire so that one system shorting it does not short everywhere.
    - want basic state to have 0 current

- joy stick
    - VRX and VRY to any GPIO, sw is just a switch
    - just use like a requglar swtich or button
    - resting state stuck at x = y = 1
    - pull_up_down=GPIO.PUD_UP for sw to work (as oppposed to pull_up_down=GPIO.PUD_DOWN)

- 3 Modes
    - did a simple thing that would print different letters based on the inputs provided

## Task 2: Interactive Device
- Idea: recreating the brick breaking game on the OLED
    - button would switch the paddle color which must match the ball color (either blue or red)
    - only the x values of the joystick would matter to move the paddle left to write
    - pushing the joystick leads to a pause menu from which you can continue or restart
    - the switch will turn on or off gravity so that you can contorl the speed of the ball
        if the bricks part proved to be too complex for the system, it would be a game of keeping the ball up in the air instead

- Coding: 
    - added some delays for debouncing and stuff like that for each of the inputs
    - all components work individually, reworked system so they got brought together

- Enclosure:
    - created a very bulky gameboy-esk thing from cardboard, got a battery from AKW127, things fit but if shaken it will be bad
        - added a back flap for easy access to stuff and cut out the button holes so that they fit snuggly enough to just plop in there (will need to add tape/glue)
    - the OLED has stopped working, tried different ports and different micro controllers, it is officially dead. Can't find any replacements in CEID or AKW

- Screen:
    - migrated code to python to use pygame to create the screen on the laptop
    - using Pyserial to communicate from ESP32 to laptop (for speed)

- Wiring:
    - forgot how to wire everything together, so creating a circuit diagram with fritzing to not forget
    - got it wired back up fine

- Integration:
    - combining the circuit with the new software, created a test.py to just test the game with keyboard keys
    - tried combining and the entire screen just went black
    - issue was the inputs were being read in wrong and I have way too many global variables
    - small issue with last_button only being set when button = 0 and last_button = 1, which happens once, led to a forever pause menu
    - organizing code

- Enclosure part II:
    - same ideas as the last enclosure, but now with no screen and an added port to connect to my computer
    - made the first enclosure out of cardboard, it was too small so remade it with much larger dimensions
    - first time at the part where we insert the components, found the bolts great for the switch and joystick, used lots of hot glue for the button.

- Added Features:
    - since the screen is much bigger I was able to add more features:
        - life counter
        - score
        - number of hits
        - a game start screen, a win screen, and a lose screen.