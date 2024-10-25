# Installation Art Project

## Overview
This project is an interactive installation that visually simulates a heartbeat using a simple, pulsating circle. Inspired by Braitenberg machines, this piece illustrates how minimal, mechanistic structures can evoke lifelike qualities. The installation uses an ESP32 microcontroller to receive real-time heart rate data, which controls the rhythmic pulsing of the circle, representing the essence of a heartbeat.

## Creative Concept
The design aims to demonstrate that even the simplest forms can convey the illusion of life. By abstracting a heartbeat as a pulsating circle, viewers are invited to connect emotionally with minimal design. The piece responds to environmental factors like light, proximity, and touch, creating an interactive experience that highlights the unseen effects of subtle interactions on "life."

## Installation and Usage

### Requirements
- ESP32 microcontroller
- Sensors:
  - Photoresistor for light sensing
  - Ultrasonic distance sensor for proximity
  - Two capacitive touch sensors
- Raspberry Pi
- Wi-Fi for real-time data transmission

### Installation
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/PM8686/CS334.git
   ```
2. **Navigate to the Project Directory:**
   ```bash
   cd CS334/InstallationArt
   ```

### Usage
1. Flick the switch and plug in the rasberry pi
2. watch it start up on boot.


## Technical Details
- **Languages and Libraries:** C++ for ESP32 programming (Arduino IDE), Python with Pygame for visualization
- **File Structure:**
  - `bpm_async.py` - Python script to render the pulsating circle based on real-time data
  - `bpm/bpm.ino` - ESP32 code to read sensor inputs and transmit heart rate data
  - mod3.service.txt - the startup file in systemd that allows for startup on boot
  - start_script - what mod3.service calls to start up the program.
  - all other files were made during the testing portions

## Videos
- **Live Demo:**
    [YouTube Link](https://youtu.be/KVCcj9UUPC8)

## Additional Notes
This project emphasizes the "unseen effect," where prolonged environmental changes subtly alter the heartbeat. The installation invites viewers to interact with the sensors and observe how subtle changes influence the rhythm, exploring how even minimalistic representations can evoke life.