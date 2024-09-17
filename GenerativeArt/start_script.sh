#!/bin/bash

# Step 1: Open a terminal
# Step 2: Navigate to the desired directory
cd /home/student334/Desktop/CS334/GenerativeArt || { echo "Directory not found"; exit 1; }

# Step 3: Start the Python HTTP server on port 8000
python -m http.server 7000 

# Step 4: Open the default web browser with the local server URL
xdg-open http://localhost:7000

# may need to use the below
# chmod +x start_server.sh
# ./start_server