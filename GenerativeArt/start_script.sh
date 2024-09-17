#!/bin/bash

# Step 1: Open a terminal
# Step 2: Navigate to the desired directory
cd /home/student334/Desktop/CS334/GenerativeArt || { echo "Directory not found"; exit 1; }

# Step 3: Start the Python HTTP server on port 7000
python -m http.server 7000 &

# Give the server a moment to start
sleep 2

# Step 4: Open Chromium with the local server URL
# Start Chromium in the background
chromium-browser --new-window  http://localhost:7000 --start-fullscreen

# # Step 5: Use wmctrl to make the Chromium window fullscreen
# # Get the window ID of the Chromium tab
# WINDOW_ID=$(wmctrl -lx | grep 'chromium-browser.Chromium-browser' | awk '{print $1}')

# # Check if we got a window ID
# if [ -n "$WINDOW_ID" ]; then
#     wmctrl -ir "$WINDOW_ID" -b toggle,fullscreen
# else
#     echo "Chromium window not found"
# fi


# may need to use the below
# chmod +x start_script.sh
# ./start_script