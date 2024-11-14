# Smart-Water-Pump-Control-with-Blynk

**Description**
This project uses the ESP32 microcontroller to monitor and control a water pump based on water levels using an ultrasonic sensor. The system also measures water flow using a flow sensor. Data is sent to the Blynk IoT platform for real-time monitoring and remote control.

Water Level Control: The water pump is automatically controlled based on the water level detected by the ultrasonic sensor.
Flow Rate Monitoring: The flow rate is calculated using pulses from the flow sensor and sent to the Blynk app.
Remote Pump Control: The pump can be manually controlled via the Blynk app using a button.

**Components Used**
ESP32: Microcontroller for WiFi and control logic.
Ultrasonic Sensor (HC-SR04): Measures the water level in the tank.
Flow Sensor: Measures the flow rate of water.
Relay Module: Controls the water pump.
Blynk: For real-time monitoring and remote control.

**Pin Configuration**
Trig Pin: GPIO 12
Echo Pin: GPIO 14
Pump Pin: GPIO 26
Flow Sensor Pin: GPIO 27

**Libraries Required**
BlynkSimpleEsp32: For Blynk integration.
WiFi: For WiFi connectivity.

**Installation Instructions**
Install the Arduino IDE and set up the ESP32 board.
**Install Libraries:**
Open the Arduino IDE and go to Sketch > Include Library > Manage Libraries, then search for and install Blynk.
**Set up Blynk:**
Create a new project in Blynk and get your Auth Token.
Replace the auth, ssid, and pass variables with your own credentials.
Upload the Code: Upload the code to your ESP32.

**How It Works**
The ultrasonic sensor measures the water level. If the water level is below a certain threshold, the pump turns on automatically to fill the tank.
The flow sensor measures the water flow and updates the flow rate every 5 seconds in the Blynk app.
The pump can be controlled manually via a button in the Blynk app, and its status is displayed in real time.

**Blynk App Configuration**
Create a Blynk project and obtain the Auth Token.
Use the following virtual pins in your Blynk app:
V0: Water Level
V1: Flow Rate
V2: Pump Control (Button)
V3: Pump Status (Label)
