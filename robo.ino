#include <Servo.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

char data;
int ledPinRed = 5;
int ledPinYellow = 6;
int ledPinGreen = 7;

int buzzerPin = 12;

int trigPin = 10;
int echoPin = 11;


int rainSensorPin = A0;

int ldrSensorPin = A1;

int buttonPin = 4;


boolean ledState = LOW;

// กำหนดพินสำหรับ LDR sensor และ servo motor
const int servoPin1 = 8;
const int servoPin2 = 9;

// สร้างอ็อบเจ็กต์สำหรับ Servo
Servo myServo1;
Servo myServo2;
bool servo = false;
bool watervo = false;
bool Door = false;
bool Day = false;
bool XX = false;
boolean prevBtnStatus = LOW;

void A(bool x){
    myServo1.write(0);
    delay(15);
    myServo2.write(180);
    delay(90);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void B(bool x){
    myServo1.write(180);
    myServo2.write(0);
    delay(170);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void C(bool x){
    myServo1.write(180);
    delay(50);
    myServo2.write(0);
    delay(90);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void D(bool x){
    myServo1.write(0);
    myServo2.write(180);
    delay(170);
    myServo1.write(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void S(bool x){
    myServo2.write(180);
    delay(90);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void E(bool x){
    myServo1.write(0);
    delay(15);
    myServo1.write(90);
    delay(100);
  servo = false;
}

void G(bool x){
    myServo1.write(180);
    delay(170);
    myServo1.write(90);
    delay(100);
  servo = false;
}

void H(bool x){
    myServo2.write(0);
    delay(170);
    myServo2.write(90);
    delay(100);
  servo = false;
}

void I(bool x){
    myServo1.write(180);
    delay(50);
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
    delay(170);
    myServo1.write(90);
    delay(100);
  servo = false;
}

void L(bool x){
    myServo2.write(180);
    delay(170);
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
  delay(10);
  digitalWrite(ledPinGreen, LOW);
  delay(10);
  digitalWrite(ledPinYellow, HIGH);
  delay(10);
  digitalWrite(ledPinYellow, LOW);
  delay(10);
  digitalWrite(ledPinRed, HIGH);
  delay(10);
  digitalWrite(ledPinRed, LOW);
  delay(10);
}

void TwinkleLED1(){
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
  delay(1);
}

void nuumalee(){
  int melody[] = {
    NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4,  NOTE_G4, NOTE_G4,
    NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4,  NOTE_C4
  };
  int noteDurations[] = {
    3, 6, 4, 4, 4, 4, 2, 4, 4, 2,     4, 4, 2,
    3, 6, 4, 4, 4, 4, 2, 4, 4, 3,     3, 1 };
  for (int thisNote = 0; thisNote < 25; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
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

  pinMode(ldrSensorPin, INPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}



void loop() {
  while (Serial.available()) // whatever the data that is coming in serially and assigning the value to the variable “data”
  {
      data = Serial.read();
  }
  boolean btnState = digitalRead(buttonPin);
  if ( btnState == HIGH && prevBtnStatus == LOW ) {
    ledState = ! ledState;
    delay( 75 );
  }
  prevBtnStatus = btnState;
  if (CheckLDR() < 300){
    if(ledState == HIGH and Day == true and Door == true){
      C(servo);
      servo = true;
      //Door = false;
      Day = false;
    }else{
    if(ledState == HIGH and Door == false){
      B(servo);
      digitalWrite(ledPinGreen, HIGH);
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinYellow, LOW);
      servo = true;
      Door = true;
      Day = false;
     }
    }
    if(ledState == LOW and Door == true){
      D(servo);
      digitalWrite(ledPinGreen, LOW);
      digitalWrite(ledPinRed, HIGH);
      digitalWrite(ledPinYellow, LOW);
      servo = true;
      Door = false;
      //Day = false;
    }
    //Day = false;
  }
  if (CheckLDR() >= 300){
    if(ledState == HIGH and Day == false and Door == true){
      A(servo);
      servo = true;
      //Door = false;
      Day = true;
    }else{
    if(ledState == HIGH and Door == false){
      G(servo);
      digitalWrite(ledPinGreen, HIGH);
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinYellow, LOW);
      servo = true;
      Door = true;
      Day = true;
     }
    }
    if(ledState == LOW and Door == true){
      K(servo);
      digitalWrite(ledPinGreen, LOW);
      digitalWrite(ledPinRed, HIGH);
      digitalWrite(ledPinYellow, LOW);
      servo = true;
      Door = false;
      //Day = false;
    }
    //Day = true;
  }
    if(data == 'A'){
      delay(1500);
      data = Serial.read();
      if(data == 'A'){
        A(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);        
      }
    }
    if(data == 'B'){
      delay(1500);
      data = Serial.read();
      if(data == 'B'){
        B(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'C'){
      delay(1500);
      data = Serial.read();
      if(data == 'C'){
        C(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'D'){
      delay(1500);
      data = Serial.read();
      if(data == 'D'){
        D(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'E'){
      delay(1500);
      data = Serial.read();
      if(data == 'E'){
        E(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'F'){
      delay(1500);
      data = Serial.read();
      if(data == 'F'){
        S(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'G'){
      delay(1500);
      data = Serial.read();
      if(data == 'G'){
        G(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'H'){
      delay(1500);
      data = Serial.read();
      if(data == 'H'){
        H(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'I'){
      delay(1500);
      data = Serial.read();
      if(data == 'I'){
        I(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'J'){
      delay(1500);
      data = Serial.read();
      if(data == 'J'){
        J(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'K'){
      delay(1500);
      data = Serial.read();
      if(data == 'K'){
        K(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
    if(data == 'L'){
      delay(1500);
      data = Serial.read();
      if(data == 'L'){
        L(servo);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, HIGH);
      }
    }
  if(CheckRain()>400 and UltrasonicSensor()>8){
    if(watervo == true){
      D(servo);
      watervo = false;
    }
  }
  if(CheckRain()<=400 and UltrasonicSensor()<=8){
    TwinkleLED1();
    //Buzzer();
    if(watervo == false){
      B(servo);
    }
    nuumalee();
    watervo = true;      
  }else if(UltrasonicSensor()<=8){
    TwinkleLED();
    Buzzer();
    if(watervo == false){
      B(servo);
    }
    watervo = true;
  }
}
