#!/bin/bash

# Open a terminal
# Navigate to the desired directory
cd /home/student334/Desktop/CS334/GenerativeArt || { echo "Directory not found"; exit 1; }

# Start the Python HTTP server on port 7002
python -m http.server 7002 &

# Give the server a moment to start
sleep 2

# make default browser size full screen
chromium-browser --new-window --start-fullscreen
pkill chromium-browser
sleep 5
# Open Chromium with the local server URL
# Start Chromium in the background
chromium-browser --new-window  http://localhost:7002 


# may need to use the below
# chmod +x start_script.sh
# ./start_script
