#include <HX711.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <SoftwareSerial.h>

// Load cell pins
const int loadCellDoutPins[] = {16, 4, 0, 2, 15, 13, 12}; // DOUT pins
const int loadCellClkPins[] = {14, 27, 26, 25, 33, 32, 35};   // CLK pins
const float servoCloseWeights[] = {20.0, 5.0, 5.0, 0.85, 0.85, 0.23, 5.0};
const long servoOpenIntervals[] = {15000, 15000, 15000, 7000, 7000, 7000, 30000};

char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourNetworkPassword";

Servo servos[7];
HX711 scales[7];
SoftwareSerial pHSerial(2, 3); // RX, TX

unsigned long previousMillis[7] = {0, 0, 0, 0, 0, 0, 0};
bool isServoOn[7] = {false, false, false, false, false, false, false};
int minServoValue = 90;
int maxServoValue = 180;

BlynkTimer timer;

void handleServo(int index, int value, int pin, int minVal, int maxVal, int intervalVal, int virtualPin) {
  if (value == minVal) {
    isServoOn[index] = false;
    servos[index].write(minVal);
    Blynk.virtualWrite(virtualPin, minVal);
  } else {
    isServoOn[index] = true;
    servos[index].write(maxVal);
    Blynk.virtualWrite(virtualPin, maxVal);
  }
}

void setup() {
  Serial.begin(9600);
  pHSerial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  for (int i = 0; i < 7; i++) {
    servos[i].attach(23 - i); // Adjust pins as per your configuration
    scales[i].begin(loadCellDoutPins[i], loadCellClkPins[i]);
    scales[i].set_scale();
  }

  timer.setInterval(1000L, updateLoadCellWeights);
  timer.setInterval(2000L, readPhSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  checkAndCloseServos();
}

void updateLoadCellWeights() {
  for (int i = 0; i < 7; i++) {
    float weight = scales[i].get_units();
    Blynk.virtualWrite(V7 + i, weight);
  }
}

void readPhSensor() {
  if (pHSerial.available() > 0) {
    String pHString = pHSerial.readStringUntil('\n');
    float pHValue = pHString
    float pHValue = pHString.toFloat();
    Blynk.virtualWrite(V14, pHValue); // Virtual pin to display pH value in Blynk app

    // Check pH value and open servo 7 if pH is less than 6.5
    if (pHValue < 6.5) {
      servos[6].write(maxServoValue);
      isServoOn[6] = true;
      Blynk.virtualWrite(13, maxServoValue); // Virtual pin for servo 7 in Blynk app
    }
  }
}