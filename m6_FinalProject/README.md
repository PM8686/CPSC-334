# Generative Art Project

## Overview
This project features a generative art piece created using p5.js. The art involves randomly sized and colored circles that appear at random locations on the canvas. Each circle gradually becomes more transparent until it disappears completely. Larger circles last longer, while smaller circles disappear more quickly. When the number of circles on the canvas reaches about 35, no new circles are added until all existing circles have disappeared, creating a repeating cycle.

## Creative Concept
The art symbolizes the process of letting go. As circles appear and fade, they represent how experiences grow in significance over time but eventually fade away. This concept reflects the transient nature of life and the inevitable cycle of letting go.

## Installation and Usage

### Requirements
- A modern web browser (e.g., Google Chrome, Firefox)
- p5.js library

### Installation
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/PM8686/CS334.git
   ```
2. **Navigate to the Project Directory:**
   ```bash
   cd CS334/GenerativeArt
   ```
3. **Set Up a Local Server:**
   This project uses a local HTTP server to serve the files. You can use Python to set up a simple server.

   If you have Python 3 installed:
   ```bash
   python -m http.server 7000
   ```
   If you have Python 2 installed:
   ```bash
   python -m SimpleHTTPServer 7000
   ```

### Usage
1. **Open the Art in Your Browser:**
   After starting the local server, open your web browser and navigate to:
   ```
   http://localhost:7000
   ```
   The generative art should now be visible and running.

### Performance Considerations
- The program dynamically adjusts to the screen size, modifying circle sizes and visibility duration accordingly.
- For optimal performance on devices like the Raspberry Pi, the pixel density is reduced to accommodate various screen sizes.

## Technical Details
- **Languages and Libraries:** JavaScript, p5.js
- **File Structure:** 
  - `index.html` - HTML file to load the p5.js sketch
  - `style.css` - CSS file for any required styling
  - `sketch.js` - p5.js script implementing the generative art
  - `start_script` - bash file to run the program and display it at full screen.

## Videos
- **Full Screen**
[![](https://markdown-videos-api.jorgenkh.no/youtube/jlBawYICgnc)](https://youtu.be/jlBawYICgnc)

- **Resizable Window**
[![](https://markdown-videos-api.jorgenkh.no/youtube/3S7aQnbZe1Y)](https://youtu.be/3S7aQnbZe1Y)
