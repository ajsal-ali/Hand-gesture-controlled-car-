#include "ESP8266WiFi.h"
#include <SoftwareSerial.h>

SoftwareSerial espSerial(-1, D5); // RX=D4, TX=D5
// enter the ssid and password of wifi 
const char* ssid = "";
const char* password = "";      
const int port = 8080; 

WiFiServer server(port); // Create a server object on the specified port

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600); // Initialize software serial communication with Arduino
  delay(10);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    
    // Read the request from the client
    while (client.connected()) {
      if (client.available()) {
        // Read the incoming byte
        char c = client.read();
        // Print the byte to the serial monitor
        Serial.write(c);
        Serial.write('\n');
        
        
        // Send the received byte to Arduino via SoftwareSerial
        espSerial.write(c);
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
    espSerial.write('\n');
  }
}