#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6PcxkEeQZ"
#define BLYNK_TEMPLATE_NAME "Four lid and food level"
#define BLYNK_AUTH_TOKEN "jtyYTDLzoM-71Ay43lmWUHlyWWnmR4xd"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <NewPing.h>

#define TRIG_PIN_1 13        // GPIO connected to the trigger pin of the first ultrasonic sensor
#define ECHO_PIN_1 12
#define TRIG_PIN_2 27       // GPIO connected to the trigger pin of the second ultrasonic sensor
#define ECHO_PIN_2 14
#define TRIG_PIN_3 25       // GPIO connected to the trigger pin of the second ultrasonic sensor
#define ECHO_PIN_3 26
#define TRIG_PIN_4 32       // GPIO connected to the trigger pin of the second ultrasonic sensor
#define ECHO_PIN_4 33

char auth[] = BLYNK_AUTH_TOKEN; // Your Blynk authentication token
char ssid[] = "Reza"; 
char pass[] = "Reza4677"; 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const long servo1OffDuration = 2000; // 2 seconds off duration
const long servo1OnDuration = 7000;   // 7 seconds on duration
const long servo2OffDuration = 2000; // 2 seconds off duration
const long servo2OnDuration = 7000;   // 7 seconds on duration
const long servo3OffDuration = 5000; // 2 seconds off duration
const long servo3OnDuration = 15000;   // 7 seconds on duration
const long servo4OffDuration = 10000; // 2 seconds off duration
const long servo4OnDuration = 15000;   // 7 seconds on duration

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;

bool isServo1On = false;
bool isServo2On = false;
bool isServo3On = false;
bool isServo4On = false;

NewPing sonar1(TRIG_PIN_1, ECHO_PIN_1);
NewPing sonar2(TRIG_PIN_2, ECHO_PIN_2);
NewPing sonar3(TRIG_PIN_3, ECHO_PIN_3);
NewPing sonar4(TRIG_PIN_4, ECHO_PIN_4);
unsigned long previousMillis_ultra = 0; // Variable to store time
const long interval_ultra = 1000;        // Interval in milliseconds

BlynkTimer timer;

BLYNK_WRITE(V1) {
    int value = param.asInt();
    if (value == 90) {
        isServo1On = false;
        servo1.write(90); 
        Blynk.virtualWrite(V1, 90);
    } else {
        isServo1On = true;
        servo1.write(180); 
        Blynk.virtualWrite(V1, 180);
    }
}

BLYNK_WRITE(V6) {
    int value = param.asInt();
    if (value == 90) {
        isServo2On = false;
        servo2.write(90); 
        Blynk.virtualWrite(V6, 90);
    } else {
        isServo2On = true;
        servo2.write(180); 
        Blynk.virtualWrite(V6, 180);
    }
}

BLYNK_WRITE(V7) {
    int value = param.asInt();
    if (value == 90) {
        isServo3On = false;
        servo3.write(90); 
        Blynk.virtualWrite(V7, 90);
    } else {
        isServo3On = true;
        servo3.write(180); 
        Blynk.virtualWrite(V7, 180);
    }
}

BLYNK_WRITE(V10) {
    int value = param.asInt();
    if (value == 90) {
        isServo4On = false;
        servo4.write(90); 
        Blynk.virtualWrite(V10, 90);
    } else {
        isServo4On = true;
        servo4.write(180); 
        Blynk.virtualWrite(V10, 180);
    }
}

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    pinMode(TRIG_PIN_1, OUTPUT);       
    pinMode(ECHO_PIN_1, INPUT);        
    pinMode(TRIG_PIN_2, OUTPUT);       
    pinMode(ECHO_PIN_2, INPUT);
    pinMode(TRIG_PIN_3, OUTPUT);       
    pinMode(ECHO_PIN_3, INPUT);
    pinMode(TRIG_PIN_4, OUTPUT);       
    pinMode(ECHO_PIN_4, INPUT);         
    servo1.attach(19); 
    servo2.attach(21);
    servo3.attach(22); 
    servo4.attach(23); 
}

void loop() {
    Blynk.run();

    unsigned long currentMillis = millis();

    //servo 1
    if (isServo1On) {
        if (currentMillis - previousMillis1 >= servo1OffDuration) {
            servo1.write(90);  
            Blynk.virtualWrite(V1, 90);
            isServo1On = false;
            previousMillis1 = currentMillis;
        }
    } else {
        if (currentMillis - previousMillis1 >= servo1OnDuration) {
            servo1.write(180); 
            Blynk.virtualWrite(V1, 180);
            isServo1On = true;
            previousMillis1 = currentMillis;
        }
    }

    //servo 2
    if (isServo2On) {
        if (currentMillis - previousMillis2 >= servo2OffDuration) {
            servo2.write(90);  
            Blynk.virtualWrite(V6, 90);
            isServo2On = false;
            previousMillis2 = currentMillis;
        }
    } else {
        if (currentMillis - previousMillis2 >= servo2OnDuration) {
            servo2.write(180); 
            Blynk.virtualWrite(V6, 180);
            isServo2On = true;
            previousMillis2 = currentMillis;
        }
    }

    //servo 3
    if (isServo3On) {
        if (currentMillis - previousMillis3 >= servo3OffDuration) {
            servo3.write(90);  
            Blynk.virtualWrite(V7, 90);
            isServo3On = false;
            previousMillis3 = currentMillis;
        }
    } else {
        if (currentMillis - previousMillis3 >= servo3OnDuration) {
            servo3.write(180); 
            Blynk.virtualWrite(V7, 180);
            isServo3On = true;
            previousMillis3 = currentMillis;
        }
    }

    //servo 4
    if (isServo4On) {
        if (currentMillis - previousMillis4 >= servo4OffDuration) {
            servo4.write(90);  
            Blynk.virtualWrite(V10, 90);
            isServo4On = false;
            previousMillis4 = currentMillis;
        }
    } else {
        if (currentMillis - previousMillis4 >= servo4OnDuration) {
            servo4.write(180); 
            Blynk.virtualWrite(V10, 180);
            isServo4On = true;
            previousMillis4 = currentMillis;
        }
    }

    unsigned long currentMillis_ultra = millis(); 

    if (currentMillis_ultra - previousMillis_ultra >= interval_ultra) {
        previousMillis_ultra = currentMillis_ultra; 

        // Readings from the first ultrasonic sensor
        unsigned int distance1 = sonar1.ping_cm();
        Blynk.virtualWrite(V3, distance1);

        if (distance1 >= 0 && distance1 <= 2) {
            Blynk.virtualWrite(V2, 100); 
        } else if (distance1 > 2 && distance1 <= 4) {
            Blynk.virtualWrite(V2, 75); 
        } else if (distance1 > 4 && distance1 <= 6) {
            Blynk.virtualWrite(V2, 50); 
        } else if (distance1 > 6 && distance1 <= 8) {
            Blynk.virtualWrite(V2, 25); 
        } else if (distance1 > 8) {
            Blynk.virtualWrite(V2, 0); 
        }

        // Readings from the second ultrasonic sensor
        unsigned int distance2 = sonar2.ping_cm();
        Blynk.virtualWrite(V5, distance2);

        if (distance2 >= 0 && distance2 <= 2) {
            Blynk.virtualWrite(V4, 100); 
        } else if (distance2 > 2 && distance2 <= 4) {
            Blynk.virtualWrite(V4, 75); 
        } else if (distance2 > 4 && distance2 <= 6) {
            Blynk.virtualWrite(V4, 50); 
        } else if (distance2 > 6 && distance2 <= 8) {
            Blynk.virtualWrite(V4, 25); 
        } else if (distance2 > 8) {
            Blynk.virtualWrite(V4, 0);
        }

        // Readings from the second ultrasonic sensor
        unsigned int distance3 = sonar3.ping_cm();
        Blynk.virtualWrite(V9, distance3);

        if (distance3 >= 0 && distance3 <= 2) {
            Blynk.virtualWrite(V8, 100); 
        } else if (distance3 > 2 && distance3 <= 4) {
            Blynk.virtualWrite(V8, 75); 
        } else if (distance3 > 4 && distance3 <= 6) {
            Blynk.virtualWrite(V8, 50); 
        } else if (distance3 > 6 && distance3 <= 8) {
            Blynk.virtualWrite(V8, 25); 
        } else if (distance3 > 8) {
            Blynk.virtualWrite(V8, 0);
        }


        // Readings from the second ultrasonic sensor
        unsigned int distance4 = sonar4.ping_cm();
        Blynk.virtualWrite(V12, distance4);

        if (distance4 >= 0 && distance4 <= 2) {
            Blynk.virtualWrite(V11, 100); 
        } else if (distance4 > 2 && distance4 <= 4) {
            Blynk.virtualWrite(V11, 75); 
        } else if (distance4 > 4 && distance4 <= 6) {
            Blynk.virtualWrite(V11, 50); 
        } else if (distance4 > 6 && distance4 <= 8) {
            Blynk.virtualWrite(V11, 25); 
        } else if (distance4 > 8) {
            Blynk.virtualWrite(V11, 0);
        }
        
    }
}
