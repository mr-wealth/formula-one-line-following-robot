#include <QTRSensors.h>

// Motor pins
#define ENA 13   // Enable pin for motor A
#define IN1 12   // Input pin 1 for motor A
#define IN2 11   // Input pin 2 for motor A
#define ENB 8   // Enable pin for motor B
#define IN3 10   // Input pin 1 for motor B
#define IN4 9   // Input pin 2 for motor B

// Sensor pins (for QTR-8)
#define sensorCount 8
const uint8_t sensorPins[sensorCount] = {0, 1, 2, 3, 4, 5, 6, 7};
QTRSensors qtr;

float Kp = 0.5; // Proportional gain
float Ki = 0.1; // Integral gain
float Kd = 0.05; // Derivative gain

int previousError = 0;
float integral = 0;

void setup() {
    Serial.begin(9600);
    qtr.setTypeAnalog();
    qtr.setSensorPins(sensorPins, sensorCount);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop() {
    unsigned long start = millis();
    
    // Read sensor values and calculate position
    uint16_t sensorValues[sensorCount];
    int position = qtr.readLineBlack(sensorValues); // Use black line detection

    // Calculate error (centered at middle sensor)
    int error = position - 3500; // Adjust this value based on your calibration

    // PID calculations
    integral += error;
    float derivative = error - previousError;

    float output = Kp * error + Ki * integral + Kd * derivative;

    previousError = error;

    // Adjust motor speeds based on PID output
    int leftSpeed = constrain(200 - output, 0, 255); // Base speed of left motor
    int rightSpeed = constrain(200 + output, 0, 255); // Base speed of right motor

    setMotorSpeeds(leftSpeed, rightSpeed);

    delay(20); // Loop delay for stability
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    if (leftSpeed > 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, leftSpeed);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, 0);
    }

    if (rightSpeed > 0) {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, rightSpeed);
    } else {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, 0);
    }
}
