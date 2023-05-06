/* Week 11.2 bidi serial example
 * Originally by Aaron Sherwood
 * Modified by Mangtronix
 *
 * Add this library to Sketch files
 *  https://github.com/mangtronix/IntroductionToInteractiveMedia/blob/master/code/p5.web-serial.js files
 *
 * You must include this line in your index.html (in Sketch Files) to load the
 * web-serial library
 *
 *     <script src="p5.web-serial.js"></script>
 *
 * Arduino code:
 * https://github.com/mangtronix/IntroductionToInteractiveMedia/blob/master/code/Week11Serial.ino
 */

let joystickInput = 0;

function setup() {
  createCanvas(640, 480);
  textSize(18);
}

function draw() {
  // one value from Arduino controls the background's red color
  background(20, 255, 255);

  if (!serialActive) {
    text("Press Space Bar to select Serial Port", 20, 30);
  } else {
    text("Connected", 20, 30);

    // Print the current values
    console.log("joystickInput = " + joystickInput);
    text("joystickInput = " + str(joystickInput), 20, 50);
    // text('alpha = ' + str(alpha), 20, 70);
  }
}

function keyPressed() {
  if (key == " ") {
    // important to have in order to start the serial connection!!
    setUpSerial();
  }
}

// This function will be called by the web-serial library
// with each new *line* of data. The serial library reads
// the data until the newline and then gives it to us through
// this callback function
function readSerial(data) {
  ////////////////////////////////////
  //READ FROM ARDUINO HERE
  ////////////////////////////////////

  if (data != null) {
    // make sure there is actually a message
    // split the message
    console.log(data);
    // if the right length, then proceed
    joystickInput = data;

    //////////////////////////////////
    //SEND TO ARDUINO HERE (handshake)
    //////////////////////////////////
    let sendToArduino = 0 + "\n";
    writeSerial(sendToArduino);
  }
}
