Abdullah Diaa, [07/05/2024 02:04 ص]
#include <Servo.h>
#include <Arduino.h>
#include <stdio.h>
   
Servo Smoto; //Servo obj
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,16,2);
//================ GAS ============
int LED_Gas = 4;
int Gas = A0;
int Fi = A1;
int buzz_S = 5;

//==========  الكراج============
Servo myservo;  // تعريف كائن سيرفو

int IR_Pin = A2; // تعريف مدخل مستشعر الأشعة تحت الحمراء
int IR2 = A5; // تعريف مدخل مستشعر الأشعة تحت الحمراء

//============= معرفة الامطار  ================
int  water_lever= A3; // تعريف مدخل مستشعر الأشعة تحت الحمراء
int waterpump= 6;
int water_Led= 7;
int moistureSensor=A9;
const int motor = 34;
const int alrm = 36;

//========================= حاوية نفايات

const int trigPin = 10;  // تعيين رقم الدخل المستخدم لدورة الاستدعاء
const int echoPin =11; // تعيين رقم الدخل المستخدم لقياس المسافة

Servo doorServo;  // تعريف كائن سيرفو

// ============================

int LEDR = 24;
int LEDG =22;
int vibration_Sensor = A4;

int present_condition = 0;
int previous_condition = 0;
// LDR
// تعريف المدخلات والمخرجات
const int ldrPin = A8;  // توصيل سنسور LDR هنا
const int ledPin = 26;  // توصيل LED هنا

// قراءة قيمة الضوء من ال LDR
int lightValue = 0;
int d=1000;
// ======
// تعريف المخارج لل LEDs
const int greenLed = 28;
const int yellowLed = 30;
const int redLed = 32;


unsigned long previousTime = 0; // متغير لتتبع الوقت السابق
const long greenDuration = 10000; // مدة الإشارة الخضراء بالميلي ثانية
const long yellowDuration = 3000; // مدة الإشارة الصفراء بالميلي ثانية
const long redDuration = 10000; // مدة الإشارة الحمراء بالميلي ثانية

int currentSignal = 0; // متغير لتتبع حالة الإشارة الحالية

const int flameSensorPin = 2;

void setup() {
  Serial.begin(9600);       // بدء الاتصال التسلسلي مع الكمبيوتر

  pinMode(LED_Gas, OUTPUT);
  pinMode(buzz_S, OUTPUT);
  pinMode(SP, OUTPUT);
  pinMode(Gas, INPUT);
  pinMode(Fi, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(water_lever, INPUT);

  myservo.attach(9);
  pinMode(IR_Pin, INPUT);
  pinMode(IR2, INPUT);

  pinMode(waterpump, OUTPUT);
  pinMode(water_Led, OUTPUT);

  doorServo.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(vibration_Sensor, INPUT);
    pinMode(ledPin, OUTPUT);  // جعل مخرج ال LED كمخرج

   lcd.init();   // initialize
  lcd.backlight();
    lcd.print("Iraqi Dinar");

  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(alrm, OUTPUT);
      myservo.write(0);

}

void loop() {
  // Serial.println(analogRead(Fi));
  // Serial.println(analogRead(Gas));
// delay(1000);
    // LCD
    lcd.clear();
  lcd.setCursor(1,0);   //(C,R)
  lcd.print("Iraqi Dinar");
  lcd.setCursor(7,1);   //(C,R)
  lcd.print(" 145 ");
    delay(100);

  // محطة الغاز
    int valFi = digitalRead(Fi);
    int valgas = analogRead(Gas);
    // digitalWrite(buzz_S, HIGH);
    // digitalWrite(LED_Gas, HIGH);

  // if ( valgas >= 120) {
  if ( valFi == 1 || valgas >= 120) {
    digitalWrite(buzz_S, HIGH);
    digitalWrite(LED_Gas, 0);
        delay(1000);

  } else {
    digitalWrite(buzz_S, LOW);
    digitalWrite(LED_Gas, 1);
  }


  // // الكراج
  // Serial.println(digitalRead(IR_Pin));
  // Serial.println(digitalRead(IR2));

  int val = digitalRead(IR_Pin);
  int val2 = digitalRead(IR2);
  if (val == 0 ||val2 == 0 ) {
    myservo.write(90);
    delay(1000);
  } else {
    myservo.write(0);
  }
       int moisture1=analogRead(moistureSensor);
       int water_lever1=analogRead(water_lever);

Abdullah Diaa, [07/05/2024 02:04 ص]
// put your main code here, to run repeatedly:
    // Serial.print("The Value of the Moisture Sensor is :");
    Serial.println(analogRead(water_lever)); 
    // digitalWrite(waterpump, 0);
    // digitalWrite(water_Led, );
  // معرفة مستوى المياه
  if (water_lever1 < 50) {
    digitalWrite(waterpump, 1);
    digitalWrite(water_Led, 0);
  } else {
    digitalWrite(waterpump, 0);
    digitalWrite(water_Led, 1);
  } 
   if (moisture1 < 700) {
    digitalWrite(alrm, HIGH);
    digitalWrite(motor, 0);
  } else {
    digitalWrite(alrm, 0);
    digitalWrite(motor, 1);
  }

  

  // قياس المسافة
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  // Serial.print("Distance: ");
  // Serial.println(distance);

  // فتح الباب
  if (distance < 10) {
    doorServo.write(90);
    delay(1000);
    doorServo.write(0);
  } else {
    doorServo.write(0);
  }

  // التحكم بالإشارة المرجعية
  previous_condition = present_condition;
  present_condition = digitalRead(A4);
  // Serial.println(present_condition);

  if (previous_condition != present_condition) {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
  } else {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
  }
  // LDR
      // digitalWrite(ledPin, HIGH); // تشغيل LED

  lightValue = analogRead(ldrPin);  // قراءة قيمة الضوء من LDR
  // Serial.print("Light Value: ");     // طباعة قيمة الضوء
  // Serial.println(lightValue);
    // digitalWrite(ledPin, HIGH); // تشغيل LED

  // إذا كانت قيمة الضوء أقل من الحد المحدد (يعني الليل)
  if (lightValue < 60) { // قد تحتاج لتعديل هذا الحد حسب الظروف الفعلية
    digitalWrite(ledPin, HIGH); // تشغيل LED
    // Serial.println("Night Time!"); // طباعة رسالة للتحقق
  } else {
    digitalWrite(ledPin, LOW); // إيقاف تشغيل LED
    // Serial.println("Day Time!"); // طباعة رسالة للتحقق
  }
  // =========
    unsigned long currentTime = millis(); // الوقت الحالي بالميلي ثانية

  // التبديل بين الإشارات عند انتهاء المدة المحددة لكل منها
  if (currentTime - previousTime >= greenDuration && currentSignal == 0) {
    currentSignal = 1;
    previousTime = currentTime;
  } else if (currentTime - previousTime >= yellowDuration && currentSignal == 1) {
    currentSignal = 2;
    previousTime = currentTime;
  } else if (currentTime - previousTime >= redDuration && currentSignal == 2) {
    currentSignal = 0;
    previousTime = currentTime;
  }

  // تحديد حالة المخارج بناءً على حالة الإشارة الحالية
  switch (currentSignal) {
    case 0:
      digitalWrite(greenLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, LOW);
      break;
    case 1:
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(redLed, LOW);
      break;
    case 2:
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, HIGH);
      break;
  }


}