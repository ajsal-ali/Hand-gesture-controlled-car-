Hand Gesture Controlled Car with Obstacle Detection
This project demonstrates how to control a car using hand gestures detected through a webcam. Additionally, the car now features obstacle detection using an ultrasonic sensor, which stops the car when an obstacle is detected within a set distance.

Components
ESP8266 WiFi Module: Establishes a WiFi connection and creates a server.
Arduino Board: Controls the car's motors and processes commands from the ESP8266.
Motor Driver (AFMotor)
Ultrasonic Sensor (HC-SR04): Detects obstacles and prevents the car from crashing.
Webcam: Captures hand gestures.
Python (OpenCV, cvzone): Detects hand gestures.
Setup Instructions
1. ESP8266 Setup
Upload the provided ESP8266 code to establish a WiFi connection and create a server. The module forwards the received commands to the Arduino.
2. Python Script
Run the Python script to detect hand gestures using OpenCV and cvzone. The script sends commands (e.g., forward, backward, left, right, stop) to the ESP8266.
3. Arduino Car Mechanism
Upload the Arduino code to control the car's motors based on commands from the ESP8266. The code also processes input from the ultrasonic sensor to stop the car when an obstacle is detected.
4. Ultrasonic Sensor Integration
The ultrasonic sensor is connected to the Arduino to detect obstacles. If an object is detected within 20 cm, the car stops automatically to avoid collisions.
Commands
f; - Move forward
b; - Move backward
l; - Turn left
r; - Turn right
s; - Stop
How It Works
ESP8266 WiFi Module
Connects to the specified WiFi network.
Creates a server to receive commands from the Python script.
Forwards commands to the Arduino via SoftwareSerial.
Python Script
Detects hand gestures using the webcam.
Sends commands to the ESP8266 server based on the detected gestures.
Arduino Car Mechanism
Controls motors using the AFMotor library based on commands received from the ESP8266.
Processes data from the ultrasonic sensor to stop the car when an obstacle is too close.
Obstacle Detection
The ultrasonic sensor checks for obstacles ahead of the car.
If an obstacle is detected within 20 cm, the car will stop automatically until the obstacle is cleared.
Conclusion
This project integrates computer vision, networking, and embedded systems to create a hand gesture-controlled car with obstacle detection. Further improvements can include more complex gestures and better motor control.
