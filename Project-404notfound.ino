#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>
// Regita Rasya Program Arduino
// Raffi Harrissalman Program DFPlayerMini
int trigger = 12; // Pin 12 untuk trigger Ultrasonik
int echo = 13;    // Pin 13 untuk echo Ultrasonik
int buzzer = 8;   // Pin 8 untuk Buzzer
int sensorStatePin = 4; // Pin 4 untuk PIR
int LED1 = 7;     // Pin 7 untuk LED1
int LED2 = 2;     // Pin 2 untuk LED2

long duration = 0;
int cm = 0;
int inch = 0;

// Setup DFPlayer Mini
SoftwareSerial mySerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer tidak terdeteksi");
    while (true); // Berhenti di sini jika DFPlayer tidak terhubung
  }
  Serial.println("DFPlayer Mini siap.");
  myDFPlayer.volume(20); // Atur volume DFPlayer (0 hingga 30)
  
  // Atur pin
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorStatePin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // Rayhan Wibawa Putra Sudirman Program Sensor Ultrasonik
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Baca gelombang echo
  duration = pulseIn(echo, HIGH);
  cm = duration * 0.034 / 2;
  inch = duration * 0.0133 / 2;

  // Cek jarak objek dan aktifkan LED1 dan buzzer jika terlalu dekat
  if (inch < 50) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED1, HIGH);
    myDFPlayer.play(1); // Mainkan track pertama sebagai notifikasi
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(LED1, LOW);
  }

  // Cetak jarak 
  if (inch < 100) {
    Serial.print("Inches: ");
    Serial.println(inch);
    Serial.print("Cm: ");
    Serial.println(cm);
  }
  
  delay(500);
  // Prima Anugerah Syabana Program Sensor PIR
  int sensorState = digitalRead(sensorStatePin);
  if (sensorState == HIGH) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED2, HIGH);
    myDFPlayer.play(2); // Mainkan track kedua untuk notifikasi PIR
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(LED2, LOW);
  }
  
  delay(500);
}