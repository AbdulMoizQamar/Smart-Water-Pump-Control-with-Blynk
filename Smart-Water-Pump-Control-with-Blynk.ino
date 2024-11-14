#define BLYNK_TEMPLATE_ID "TMPL6g7pgpcn2" // Original Template ID
#define BLYNK_TEMPLATE_NAME "Water Pump " // Original Template Name
#define BLYNK_AUTH_TOKEN "fb1LBLC2O40Lv2-YbbUdf7UAcyrEnLqJ" // Original Auth Token

#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Define pins for sensors and pump
const int trigPin = 12;
const int echoPin = 14;
const int pumpPin = 26; // Controls the pump via a relay
const int flowSensorPin = 27;

long duration;
float distance;

// Variables for water flow sensor
volatile int pulseCount;
float flowRate;

// Threshold distance for water level (in cm)
const float minWaterLevel = 5.0; // Minimum distance for water level

// WiFi and Blynk credentials
char auth[] = "fb1LBLC2O40Lv2-YbbUdf7UAcyrEnLqJ"; // Blynk Auth Token
char ssid[] = "[H*m£]"; // WiFi SSID
char pass[] = "0900786010"; // WiFi Password

// Interrupt function to count flow sensor pulses
void IRAM_ATTR countPulse() {
  pulseCount++;
}

// Virtual pin assignments in Blynk
#define VIRTUAL_WATER_LEVEL V0
#define VIRTUAL_FLOW_RATE V1
#define VIRTUAL_PUMP_CONTROL V2
#define VIRTUAL_PUMP_STATUS V3 // New virtual pin for displaying pump status

unsigned long lastFlowUpdate = 0; // Store last update time
const unsigned long flowInterval = 5000; // Update flow rate every 5 seconds

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi and Blynk
  Blynk.begin(auth, ssid, pass);

  // Pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(flowSensorPin, INPUT);

  // Attach interrupt for flow sensor
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), countPulse, RISING);

  // Turn pump off initially
  digitalWrite(pumpPin, LOW);
  Blynk.virtualWrite(VIRTUAL_PUMP_STATUS, "OFF");
}

// Blynk function to control pump via app button
BLYNK_WRITE(VIRTUAL_PUMP_CONTROL) {
  int pumpState = param.asInt(); // 0 = OFF, 1 = ON
  digitalWrite(pumpPin, pumpState);
  Blynk.virtualWrite(VIRTUAL_PUMP_STATUS, pumpState ? "ON" : "OFF"); // Display pump status
  Serial.println(pumpState ? "Pump ON - Controlled by Blynk" : "Pump OFF - Controlled by Blynk");
}

void loop() {
  Blynk.run(); // Run Blynk connection

  // Measure water level using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm

  // Update flow rate every 5 seconds
  if (millis() - lastFlowUpdate >= flowInterval) {
    flowRate = (pulseCount / 7.5); // Assuming sensor produces 7.5 pulses per liter
    pulseCount = 0; // Reset pulse count after calculating flow rate
    lastFlowUpdate = millis(); // Update last time

    // Send flow rate to Blynk
    Blynk.virtualWrite(VIRTUAL_FLOW_RATE, flowRate);
    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");
  }

  // Automatic pump control based on water level
  if (distance > minWaterLevel) {
    digitalWrite(pumpPin, HIGH); // Turn on pump if water level is low
    Blynk.virtualWrite(VIRTUAL_PUMP_STATUS, "ON");
    Serial.println("Pump ON - Filling Tank");
  } else {
    digitalWrite(pumpPin, LOW); // Turn off pump if water level is sufficient
    Blynk.virtualWrite(VIRTUAL_PUMP_STATUS, "OFF");
    Serial.println("Water Level OK - Pump OFF");
  }

  // Send water level to Blynk
  Blynk.virtualWrite(VIRTUAL_WATER_LEVEL, distance);

  delay(1000); // Delay for stability
}
