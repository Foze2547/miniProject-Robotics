#include <Servo.h>

char data;
int ledPinRed = 5;
int ledPinYellow = 6;
int ledPinGreen = 7;

int buzzerPin = 12;

int trigPin = 10;
int echoPin = 11;

int pirSensorPin = 13;

int rainSensorPin = A0;

int ldrSensorPin = A1;

int buttonPin = 4;

boolean prevBtnStatus = LOW;

// กำหนดพินสำหรับ LDR sensor และ servo motor
const int servoPin1 = 8;
const int servoPin2 = 9;

// สร้างอ็อบเจ็กต์สำหรับ Servo
Servo myServo1;
Servo myServo2;
bool servo = false;
bool watervo = false;

void A(bool x){
    myServo1.write(0);
    myServo2.write(180);
    delay(75);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void B(bool x){
    myServo1.write(180);
    myServo2.write(0);
    delay(150);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void C(bool x){
    myServo1.write(180);
    myServo2.write(0);
    delay(75);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void D(bool x){
    myServo1.write(0);
    myServo2.write(180);
    delay(150);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void S(bool x){
    myServo2.write(180);
    delay(75);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void E(bool x){
    myServo1.write(0);
    delay(75);
    myServo1.write(90);
    delay(100);
  servo = false;
}

void G(bool x){
    myServo1.write(180);
    delay(150);
    myServo1.write(90);
    delay(100);
  servo = false;
}

void H(bool x){
    myServo2.write(0);
    delay(150);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void I(bool x){
    myServo1.write(180);
    delay(75);
    myServo1.write(90);
    delay(100);
  servo = false;
}

void J(bool x){
    myServo2.write(0);
    delay(75);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void K(bool x){
    myServo1.write(0);
    delay(150);
    myServo1.write(90);
    delay(100);
  servo = false;
}

void L(bool x){
    myServo2.write(180);
    delay(150);
    myServo2.write(90);
    delay(100);
  servo = false;
}

long UltrasonicSensor() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToCentimeters(duration);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
  return distance;
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

void CheckPIR(){
  if (digitalRead(pirSensorPin) == HIGH) {
    Serial.println("Motion detected!");
    delay(100);
  }
  else {
    Serial.println("No motion detected.");
    delay(100);
  }
}

int CheckRain(){
  int valueRain = analogRead(rainSensorPin);
  Serial.print("Rain Sensor value: ");
  Serial.println(valueRain);
  delay(100);
  return valueRain;
}

int CheckLDR(){
  int valueLDR = analogRead(ldrSensorPin);
  Serial.print("LDR Sensor Value = ");
  Serial.println(valueLDR);
  delay(500);
  return valueLDR;
}

void EmergencyStop(){
  OpenLEDRed(false);
  OpenLEDYellow(false);
  OpenLEDGreen(false);
  myServo1.write(90);
  myServo2.write(90);
}

void ButtomSwitch(){
  boolean btnStatus = digitalRead(buttonPin);
  if (btnStatus == HIGH && prevBtnStatus == LOW) {
    EmergencyStop();
    delay(200);
  }
  //prevBtnStatus = btnStatus;
}

//น้ำท่วม
void Water(){
  if(CheckRain()<=400 and UltrasonicSensor()<=8){
    TwinkleLED();
    Buzzer();
  }

}

void OpenLEDRed(bool Red){
  digitalWrite(ledPinRed, Red);
}

void OpenLEDYellow(bool Yellow){
  digitalWrite(ledPinYellow, Yellow);
}

void OpenLEDGreen(bool Green){
  digitalWrite(ledPinGreen, Green);
}

//ไฟกระพริบ
void TwinkleLED(){
  digitalWrite(ledPinGreen, HIGH);
  delay(100);
  digitalWrite(ledPinGreen, LOW);
  delay(100);
  digitalWrite(ledPinYellow, HIGH);
  delay(100);
  digitalWrite(ledPinYellow, LOW);
  delay(100);
  digitalWrite(ledPinRed, HIGH);
  delay(100);
  digitalWrite(ledPinRed, LOW);
  delay(100);
}

void Buzzer(){
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}

void setup() {
  myServo1.attach(servoPin1);//Right
  myServo2.attach(servoPin2);//Left
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(pirSensorPin, INPUT);
  pinMode(ldrSensorPin, INPUT);
  pinMode(buttonPin, INPUT);


  Serial.begin(9600);
}



void loop() {
  while (Serial.available()) // whatever the data that is coming in serially and assigning the value to the variable “data”
  {
      data = Serial.read();
  }
  delay(1500);
  if (CheckLDR() >= 200 && servo == false){
    delay(1000);
    B(servo);
    servo = true;
  }
  if (CheckLDR() < 200 && servo == true){
    A(servo);
    servo = false;
  }
  if (CheckLDR() < 200){
    if(data == 'A'){
      delay(1500);
      data = Serial.read();
      if(data == 'A'){
        A(servo);
      }
    }
    if(data == 'B'){
      delay(1500);
      data = Serial.read();
      if(data == 'B'){
        B(servo);
      }
    }
    if(data == 'C'){
      delay(1500);
      data = Serial.read();
      if(data == 'C'){
        C(servo);
      }
    }
    if(data == 'D'){
      delay(1500);
      data = Serial.read();
      if(data == 'D'){
        D(servo);
      }
    }
    if(data == 'E'){
      delay(1500);
      data = Serial.read();
      if(data == 'E'){
        E(servo);
      }
    }
    if(data == 'F'){
      delay(1500);
      data = Serial.read();
      if(data == 'F'){
        S(servo);
      }
    }
    if(data == 'G'){
      delay(1500);
      data = Serial.read();
      if(data == 'G'){
        G(servo);
      }
    }
    if(data == 'H'){
      delay(1500);
      data = Serial.read();
      if(data == 'H'){
        H(servo);
      }
    }
    if(data == 'I'){
      delay(1500);
      data = Serial.read();
      if(data == 'I'){
        I(servo);
      }
    }
    if(data == 'J'){
      delay(1500);
      data = Serial.read();
      if(data == 'J'){
        J(servo);
      }
    }
    if(data == 'K'){
      delay(1500);
      data = Serial.read();
      if(data == 'K'){
        K(servo);
      }
    }
    if(data == 'L'){
      delay(1500);
      data = Serial.read();
      if(data == 'L'){
        L(servo);
      }
    }
  }
  if(CheckRain()<=400 and UltrasonicSensor()<=8){
    TwinkleLED();
    Buzzer();
    if(watervo == false){
      B(servo);
      watervo = true;      
    }
  }
  if(CheckRain()>400 and UltrasonicSensor()>8){
    watervo = false;
  }
}