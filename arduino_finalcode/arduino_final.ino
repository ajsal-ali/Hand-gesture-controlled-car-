#include "Arduino.h"
#include <AFMotor.h>
#include <SoftwareSerial.h>

const int trigPin=8;
const int echoPin =7;

#define motor 10
#define fSpeed 170
#define bSpeed 140
        
#define TURN_SPEED 140
#define spoint 103

SoftwareSerial mySerial(2, -1); 

String messageBuffer = "";
float distance=1;
String lastReceivedCommand =""; 


String value = "";
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;

String command = "";

AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);


void setup() {

  mySerial.begin(9600); // Initialize serial communication with ESP8266
  Serial.begin(9600); // For debugging, initialize serial communication with computer
  Serial.println("Arduino is ready to receive messages.");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


}

void loop() {
  if (mySerial.available()) { // Check if data is available to read from ESP
    char data = (char)mySerial.read();  
    if (data == '\n' || data == '\r') {  
      return;
    }
    if (data == ';') {
      executeCommand();
      // printMessage();
    } else {
      messageBuffer += data;
    }
  }
  
  distance = getDistance();
 
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance <18 && lastReceivedCommand == "f" ){
    executeCommand();
  }
  
  delay(200);
}


void executeCommand() {
  command = messageBuffer;
  lastReceivedCommand = command;
  Serial.println("Command received: " + command); // Print command to serial monitor for debugging
  messageBuffer = ""; // Clear the message buffer for the next command

  Stop(); // Ensure motors are stopped before executing a new command
  // distance = getDistance();
  Serial.print("current distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 18 && lastReceivedCommand == "f") {
      Stop(); // Stop the robot
      Serial.println("Distance is less than 20 cm. Stopping.");
      Serial.println("command while stopping: " + command);
      messageBuffer = "";
      return; // Exit the function
    }
  if (command == "f") {
      M1.setSpeed(fSpeed);
      M2.setSpeed(fSpeed);
      M3.setSpeed(fSpeed);
      M4.setSpeed(fSpeed);
    forward();
  } else if (command == "b") {
      M1.setSpeed(bSpeed);
  M2.setSpeed(bSpeed);
  M3.setSpeed(bSpeed);
  M4.setSpeed(bSpeed);
    backward();
  } else if (command == "l") {
    M1.setSpeed(TURN_SPEED);
    M2.setSpeed(TURN_SPEED);
    M3.setSpeed(TURN_SPEED);
    M4.setSpeed(TURN_SPEED);
    left();
    // delay(1000);
    // Stop();
  } else if (command == "r") {
    M1.setSpeed(TURN_SPEED);
    M2.setSpeed(TURN_SPEED);
    M3.setSpeed(TURN_SPEED);
    M4.setSpeed(TURN_SPEED);
    right();
    // delay(1000);
    // Stop();
  } else if (command == "s") {
    Stop();
  }
}
void printMessage() {
  Serial.println("Message received from ESP8266: " + messageBuffer); // Print the received message to serial monitor
  messageBuffer = ""; // Clear the message buffer for the next message
}


// Motor control functions remain unchanged

void backward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void forward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void left() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
  // delay(5000);
  // Stop();

}

void right() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
  // delay(5000);
  // Stop();
}

void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

float getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);


    float distance_cm = duration * 0.034 / 2; // Divide by 2 because the sound travels forth and back
    // Serial.println(distance_cm);

    return distance_cm;
}