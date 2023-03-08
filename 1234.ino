#include <Servo.h>
#include <Bounce2.h>

int trigPin = 10;
int echoPin = 11;
int ledPin1 = 5;
int ledPin2 = 6;
int ledPin3 = 7;
int buzzerPin = 12;
int rainSensorPin = A0;

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
Servo myServo;

void setup() {
  // เริ่มต้นค่า LDR sensor และ servo motor
  pinMode(ldrPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(45);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // กำหนด pinMode และเปิดการใช้งาน debounce สำหรับ push button
  pinMode(buttonPin, INPUT_PULLUP);
  button.attach(buttonPin);
  button.interval(5);

  // กำหนดให้ขา PIR Sensor เป็น Input
  pinMode(pirPin, INPUT);

  // กำหนดให้ขา Servo เป็น Output
  myServo.attach(servoPin);

  // เปิด Serial communication สำหรับ debugging
  Serial.begin(9600);
}

void loop() {
  // อ่านค่าจาก LDR sensor
  int light_value = analogRead(ldrPin);

  // คำนวณค่ามุมของ servo motor จากค่าความสว่าง
  int angle = 45 + int((light_value - min_light) * (90.0 / (max_light - min_light)));

  // ควบคุม servo motor ตามค่ามุมที่คำนวณได้
  myServo.write(angle);

  // อ่านค่าจาก Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration / 58;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ตรวจจับฝน
  int rainValue = analogRead(rainSensorPin);

  Serial.print("Rain Value: ");
  Serial.println(rainValue);

  // อ่านสถานะของ push button
  button.update();

  // อ่านค่าจาก PIR Sensor
  int pirState = digitalRead(pirPin);

  // ควบคุม LED ด้วยค่าความสว่าง
  if (light_value < 500) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
  }
  // ถ้ามีน้ำท่วมเกินค่าที่กำหนด
  if (distance <= minimumDistance && rainValue >= maximumRainValue) {
    digitalWrite(ledPin1, HIGH); // เปิด LED
    tone(buzzerPin, 1000); // เล่นเสียง Buzzer
    delay(500);
    noTone(buzzerPin);
    delay(500);
    myServo.write(90); // หมุน Servo ไปที่มุม 90 องศา
  }
  else {
    digitalWrite(ledPin1, LOW); // ปิด LED
    myServo.write(0); // หมุน Servo ไปที่มุม 0 องศา
  }
  // ถ้ามีการกด push button
  if (button.fell()) {
    // หยุดการทำงานทั้งหมด
    while (true) {
      digitalWrite(ledPin1, HIGH);
      delay(500);
      digitalWrite(ledPin1, LOW);
      delay(500);
    }
  }
  // ถ้าตรวจพบการเคลื่อนไหว หยุดการทำงานของ Servo
  if (pirState == HIGH) {
    myServo.detach();
  }
  // ถ้าไม่ตรวจพบการเคลื่อนไหว กำหนดให้ Servo เคลื่อนไหวตามปกติ
  else {
    myServo.attach(servoPin);
    myServo.write(90);
    delay(1000);
    myServo.write(0);
    delay(1000);
  }

  // ส่งค่าความสว่างและมุมของ servo motor ออกไปทาง Serial communication
  Serial.print("Light Value: ");
  Serial.print(light_value);
  Serial.print(", Angle: ");
  Serial.println(angle);

  // รอเพื่อให้ข้อมูลถูกอัพเดต
  delay(100);
}
