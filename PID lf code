#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t sensorCount = 6;
uint16_t sensorValues[sensorCount];

const int ena_pin, in1_pin, in2_pin, enb_pin, in3_pin, in4_pin;
ena_pin = 15; enb_pin = 14; in1_pin = 8; in2_pin = 7; in3_pin = 6; in4_pin = 5;

//pid consts and vars
float kp, ki, kd; kp = ki = kd = 0;
int P, I, D, derivative, integral, prevError, error, m1_speed, m2_speed;

//motor speeds
int m1_baseSpeed, m2_baseSpeed, m1_maxSpeed, m2_maxSpeed;
m1_baseSpeed = 100;
m2_baseSpeed = 100;
m1_maxSpeed = 250;
m2_maxSpeed = 250;

void Calibrate(){
  //turn robot left
  digitalWrite(in1_pin, LOW); digitalWrite(in2_pin,HIGH); //left motor turns anti-clockwise
  digitalWrite(in3_pin, HIGH); digitalWrite(in4_pin,LOW);//right motor turns clockwise

  for(uint16_t i = 0; i < 200; i++){
    qtr.calibrate();
    delay(20);
  }

  //motors off
  digitalWrite(in1_pin, LOW); digitalWrite(in2_pin,LOW); 
  digitalWrite(in3_pin, HIGH); digitalWrite(in4_pin,HIGH);
  delay(500);

  //turn robot right
  digitalWrite(in1_pin, HIGH); digitalWrite(in2_pin,LOW); //left motor turns clockwise
  digitalWrite(in3_pin, LOW); digitalWrite(in4_pin,HIGH); //right motor turns anti-clockwise

  for(uint16_t i = 0; i < 400; i++){
    qtr.calibrate();
    delay(20);
  }

  digitalWrite(in1_pin, LOW); digitalWrite(in2_pin,LOW); 
  digitalWrite(in3_pin, HIGH); digitalWrite(in4_pin,HIGH);
  delay(500);

  digitalWrite(in1_pin, LOW); digitalWrite(in2_pin,HIGH); //left motor turns anti-clockwise
  digitalWrite(in3_pin, HIGH); digitalWrite(in4_pin,LOW);//right motor turns clockwise

  for(uint16_t i = 0; i < 300; i++){
    qtr.calibrate();
    delay(20);
  }

  digitalWrite(in1_pin, LOW); digitalWrite(in2_pin,LOW); 
  digitalWrite(in3_pin, HIGH); digitalWrite(in4_pin,HIGH);
  delay(2000);
}

void setup(){
  //configure motor pins
  pinMode(ena_pin, OUTPUT);
  pinMode(enb_pin, OUTPUT);
  pinMode(in1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);
  pinMode(in3_pin, OUTPUT);
  pinMode(in4_pin, OUTPUT);


  //configure lf sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){19, 16, 13, 12, 11, 10}, SensorCount);
  //qtr.setEmitterPin(2);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); //arduino led on while calibrating

  Calibrate();
  digitalWrite(LED_BUILTIN, LOW); //arduino led off after calibration
}

void PID(){
  unint16_t position = qtr.readLineBlack(sensorValues);
  error = position - 2500; //if it doesn't work, try error = 2500 - position
  P = error * kp;

  integral += error;
  I = integral * ki;

  derivative = error - prevError;
  D = derivative * kd;

  float PID = P+I+D;

  m1_speed = m1_baseSpeed + PID;
  m2_speed = m2_baseSpeed - PID;

  if(m1_speed > m1_maxSpeed){
    m1_speed = m1_maxSpeed;
  }
  if(m2_speed > m2_maxSpeed){
    m2_speed = m2_maxSpeed;
  }
  if(m1_speed < 0){
    m1_speed = 0;
  }
  if(m2_speed < 0){
    m2_speed = 0;
  }

  error = prevError;
}

/*this function was in the code I learnt from and I don't understand it yet
I think it's for speed control and breaking or something. Will check it out
when I test it.
void forward_brake(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  digitalWrite(aphase, LOW);
  digitalWrite(bphase, HIGH);
  analogWrite(aenbl, posa);
  analogWrite(benbl, posb);
}
*/
void loop() {
  //will code a button or something to start the line following later
  PID();

}
