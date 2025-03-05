# Drone project

## This is repo is for the microcontroller code

## ESP32

ESP32 will handle the communication between the drone and the control device (phone). 
It will also act as a WiFi access point, providing a network to control the drone.

Code is written in ArduinoIDE using mostly 3rd party libraries and own code where needed.

## STM32

STM32 is the actual controller for the drone motors. It communicates with the ESP through UART, 
receiving directional inputs, which are sent from the control device (phone), for the motors.