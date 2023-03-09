#include <Servo.h>
#include <Bounce2.h>

char data;
int trigPin = 10;
int echoPin = 11;
int ledPinR = 5;
int ledPinY = 6;
int ledPinG = 7;
int buzzerPin = 12;
int rainSensorPin = A0;
unsigned long previousMillis = 0;  // เก็บค่าเวลาปัจจุบัน
const unsigned long interval = 3000; // เวลาที่ต้องการค้างไว้ก่อนจะทำงาน (3 วินาที)

// กำหนดพินสำหรับ LDR sensor และ servo motor
const int ldrPin = A1;
const int servoPin1 = 8;
const int servoPin2 = 9;

// กำหนดค่าคงที่สำหรับอ่านค่า LDR
const int min_light = 0;
const int max_light = 1023;

int minimumDistance = 10; // ระยะต่ำสุดที่ตรวจจับได้ (ซม.)
int maximumDistance = 100; // ระยะสูงสุดที่ตรวจจับได้ (ซม.)
int maximumRainValue = 300; // ค่าอ่านของ Rain Sensor ที่ถือว่าเป็นฝนตก

// กำหนดชื่อพอร์ตที่เชื่อมต่อ push button
const int buttonPin = 2;

// กำหนดตัวแปรเก็บขา PIR Sensor
int pirPin = 3;

// สร้าง object ของ library Bounce
Bounce button = Bounce();

// สร้างอ็อบเจ็กต์สำหรับ Servo
Servo myServo1;
Servo myServo2;
bool servo = false;

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

void ultrasonic(){
  long duration, cm;

  pinMode(trigPin, OUTPUT); 

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = microsecondsToCentimeters(duration);

  Serial.println(cm);
  delay(100);
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}
void setup() {
  // เริ่มต้นค่า LDR sensor และ servo motor
  pinMode(ldrPin, INPUT);
  myServo1.attach(servoPin1);
  myServo2.attach(servoPin2);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // กำหนด pinMode และเปิดการใช้งาน debounce สำหรับ push button
  pinMode(buttonPin, INPUT_PULLUP);
  button.attach(buttonPin);
  button.interval(5);

  // กำหนดให้ขา PIR Sensor เป็น Input
  pinMode(pirPin, INPUT);

  // กำหนดให้ขา Servo เป็น Output
  myServo1.attach(servoPin1);//Right
  myServo2.attach(servoPin2);//Left

  // เปิด Serial communication สำหรับ debugging
  Serial.begin(9600);
}



void loop() {
  while (Serial.available())    //whatever the data that is coming in serially and assigning the value to the variable “data”
{ 
  data = Serial.read(); 
}
    delay(1500);
  if(data == 'A'){
    delay(1500);
    data = Serial.read();
    if(data == 'A'){
      servo = true;
      A(servo);
    }
  }
  if(data == 'B'){
    delay(1500);
    data = Serial.read();
    if(data == 'B'){
      servo = true;
      B(servo);
    }
  }
  if(data == 'C'){
    delay(1500);
    data = Serial.read();
    if(data == 'C'){
      servo = true;
      C(servo);
    }
  }
  if(data == 'D'){
    delay(1500);
    data = Serial.read();
    if(data == 'D'){
      servo = true;
      D(servo);
    }
  }
  if(data == 'E'){
    delay(1500);
    data = Serial.read();
    if(data == 'E'){
      servo = true;
      E(servo);
    }
  }
  if(data == 'F'){
    delay(1500);
    data = Serial.read();
    if(data == 'F'){
      servo = true;
      S(servo);
    }
  }
  if(data == 'G'){
    delay(1500);
    data = Serial.read();
    if(data == 'G'){
      servo = true;
      G(servo);
    }
  }
  if(data == 'H'){
    delay(1500);
    data = Serial.read();
    if(data == 'H'){
      servo = true;
      H(servo);
    }
  }
  if(data == 'I'){
    delay(1500);
    data = Serial.read();
    if(data == 'I'){
      servo = true;
      I(servo);
    }
  }
  if(data == 'J'){
    delay(1500);
    data = Serial.read();
    if(data == 'J'){
      servo = true;
      J(servo);
    }
  }
  if(data == 'K'){
    delay(1500);
    data = Serial.read();
    if(data == 'K'){
      servo = true;
      K(servo);
    }
  }
  if(data == 'L'){
    delay(1500);
    data = Serial.read();
    if(data == 'L'){
      servo = true;
      L(servo);
    }
  }
}