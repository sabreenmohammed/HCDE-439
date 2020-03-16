# Final project

This contraption lets you tell Alexa to make your bed.

## How it works

You can do 2 main things: tell Alexa to "make the bed" and tell her to "unmake the bed". Alexa processes the recording of your voice and figures out which of the two you're trying to do, and sends this intent to AWS Lambda. AWS Lambda cleans this information up and sends a POST request to a Particle.io server with key info about whether the motor needs to be turned clockwise or anticlockwise. Particle receives this information and makes function calls on the Particle Photon device, which is connected to your home's WiFi network.  

## Tools and Materials 

-Alexa Skills Kit
-AWS Lambda
-Particle Photon
-Drill
-Threaded rod
-20V lithium ion battery
-MDF boards, wood planks
-Laser cutter and accompanying software
-Adobe Illustrator
-Rope
-Eyebolts 
-Washers
-Corner braces
-1 AWG copper wire cable
-4 relay board

## Diagrams

![Image](Capture4.PNG)


