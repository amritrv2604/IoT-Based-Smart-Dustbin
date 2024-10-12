#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>  // Include the Blynk library for ESP8266

char auth[] = "YourAuthToken";  // Replace with your Blynk auth token
char ssid[] = "YourWiFiSSID";   // Replace with your WiFi network SSID
char pass[] = "YourWiFiPassword";  // Replace with your WiFi password

Servo servoMain; // Define our Servo
int trigpin = 4;
int echopin = 3;
int distance;
float duration;

float cm;

void setup()
{
  servoMain.attach(5);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  
  // Initialize Blynk connection
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();  // Executes Blynk's operations

  digitalWrite(trigpin, LOW);
  delay(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  cm = (duration / 58.82);
  distance = cm;

  if (distance < 30)
  {
    servoMain.write(180); // Open the dustbin
    Blynk.virtualWrite(V1, 180);  // Send servo position to Blynk (virtual pin V1)
    delay(3000);
  }
  else
  {
    servoMain.write(0); // Close the dustbin
    Blynk.virtualWrite(V1, 0);  // Send servo position to Blynk (virtual pin V1)
    delay(50);
  }
}
