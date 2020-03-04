# Assignment 6: The web talks back

In this assignment, we used serial communication to write to write sensor data to a webpage. We also listened for events on our webpage and used them to trigger activity on our board.

![Image](schematic.JPG)

My circuit uses two sensors to control the position of boxes on the screen. 
1. Blocking light from the photoresistor moves the first box right, while shining more light moves the first box left.
2. Warming the thermistor moves the second box left, while letting it cool moves it right.

![Image](incoming.gif)

My webpage also listens for click events, and determines whether one of the boxes are being clicked. Each box lights up a different LED.

![Image](outgoing.gif)

## Code

### Arduino Code 
```
void setup(){
  Serial.begin(9600);
}

void loop(){
  String output = "[";
  output = output + analogRead(A1) + "," + analogRead(A2) + "]";
  Serial.println(output);
  if (Serial.available() > 0) {   // if there's serial data 
   int inByte = Serial.read(); // read it
   int ledNum = bitRead(inByte, 0) + 9;
   digitalWrite(ledNum, HIGH); // use it to set the LED brightness
   delay(2000);
   digitalWrite(ledNum, LOW); // use it to set the LED brightness

  }  

  delay(50); 
}

```

### p5.js code

```
var serial; // variable to hold an instance of the serialport library
var portName = 'COM6'; //rename to the name of your port
var datain; //some data coming in over serial!
var xPos = 0;


function setup() {
  serial = new p5.SerialPort();       // make a new instance of the serialport library
  serial.on('list', printList);       // set a callback function for the serialport list event
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen);        // callback for the port opening
  serial.on('data', serialEvent);     // callback for when new data arrives
  serial.on('error', serialError);    // callback for errors
  serial.on('close', portClose);      // callback for the port closing
 
  serial.list();                      // list the serial ports
  serial.open(portName);              // open a serial port
  createCanvas(1200, 800);
  background(0x08, 0x16, 0x40);
}
 
// get the list of ports:
function printList(portList) {
 // portList is an array of serial port names
 for (var i = 0; i < portList.length; i++) {
 // Display the list the console:
   print(i + " " + portList[i]);
 }
}

function serverConnected() {
  print('connected to server.');
}
 
function portOpen() {
  print('the serial port opened.')
}
 
function serialError(err) {
  print('Something went wrong with the serial port. ' + err);
}
 
function portClose() {
  print('The serial port closed.');
}

function serialEvent() {
  if (serial.available()) {
  	datain = Number(serial.readLine());
        //console.log(datain);
  } 
}

function graphData(newData) {
  // map the range of the input to the window height:
  var yPos = map(newData, 0, 255, 0, height);
  // draw the line in a pretty color:
  stroke(255, 0, 80);
  line(xPos, height, xPos, height - yPos);
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    // clear the screen by resetting the background:
    background(0x08, 0x16, 0x40);
  } else {
    // increment the horizontal position for the next reading:
    xPos++;
  }
}

function draw() {
  background(255,255,255); //resets the background to white
  if (datain > 0) //skips the null inputs
	text(("2 sensors added together: " + datain), datain/5,30); // changes the position of the code
}

```
