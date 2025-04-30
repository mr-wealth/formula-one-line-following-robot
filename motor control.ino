//basic code to control motor speed and direction using the L298N motor driver

const int ENA_PIN = 6; //ENA pins control speed of the motors
const int IN1_PIN = 7;
const int IN2_PIN = 8;

void setup(){
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
}

void loop() {
  digitalWrite(IN1_PIN, HIGH); // control motor A spins clockwise
  digitalWrite(IN2_PIN, LOW); // control motor A spins clockwise

  for(int speed = 0; speed <= 255; speed++){
    analogWrite(ENA_PIN, speed); //controls speed
    delay(10);
  }
  delay(1000); //rotates at maximum speed for 1 second in clockwise direction

  //change direction
  digitalWrite(IN1_PIN, LOW); // control motor A spins anti-clockwise
  digitalWrite(IN1_PIN, HIGH); // control motor A spins anti-clockwise

  delay(1000);

  for (int speed = 255; speed >= 0; speed--){
    analogWrite(ENA_PIN, speed); //controls speed
    delay(10);
  }
  delay(1000);
}
