#include <Servo.h>

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

void setup() {
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

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
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

void loop(){

}
