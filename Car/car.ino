#include <SoftwareSerial.h>

// Enables for the L293d
#define ENABLE_1 10
#define ENABLE_2 11

// left motor
#define DIRA 8    
#define DIRB 9

// right motor
#define DIRC 12
#define DIRD 13

// HC-SR04 ultra-sonic sensor
#include "SR04.h"
#define TRIG_PIN 2
#define ECHO_PIN 3
#define led 4

SoftwareSerial BTserial(10, 11);

int state = 0;

// sensor
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance;


SoftwareSerial BluetoothSerial(7, 6);


void setup() {
  Serial.begin(9600);
 
  //---set pin direction
  pinMode(ENABLE_1, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);
 
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(DIRC, OUTPUT);
  pinMode(DIRD, OUTPUT);

  pinMode(led, OUTPUT);

  Serial.println("Enter AT commands:");
  BluetoothSerial.begin(9600);
}

void loop() {
  Serial.println("Accessing Sensor ..");
//  distance = sr04.Distance();
//  Serial.print(distance);
    sensor();
 
  if (BluetoothSerial.available() > 0) {
    state = BluetoothSerial.read();
    switch(state) {
      case 'S':
        Stop();
        break;
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'O':
        Fleft();
        break;
      case 'N':
        Fright();
        break;
      case 'P':
        Bleft();
        break;
      case 'M':
        Bright();
        break;  
    }
  }

 
  if(BluetoothSerial.available()){
    Serial.write(BluetoothSerial.read());
  }
 
  if(BluetoothSerial.available()){
    BluetoothSerial.write(Serial.read());
  }
}

void forward() {
//  sensor();
  analogWrite(ENABLE_1, 255); // enable on
  analogWrite(ENABLE_2, 125); // enable on
 
  // turn the right motor
  digitalWrite(DIRA, HIGH); //one way
  digitalWrite(DIRB, LOW);

  // turn the left motor
  digitalWrite(DIRC, HIGH);  //one way
  digitalWrite(DIRD, LOW);
}

void back() {
//  sensor();
  analogWrite(ENABLE_1, 255); // enable on
  analogWrite(ENABLE_2, 125); // enable on

  // turn the right motor
  digitalWrite(DIRA,LOW); //reverse
  digitalWrite(DIRB,HIGH);

  // turn the left motor
  digitalWrite(DIRC, LOW);  //reverse
  digitalWrite(DIRD, HIGH);
}

void left() {
//  sensor();
  analogWrite(ENABLE_1, 255); // enable on

  // turn the right motor
  digitalWrite(DIRA, HIGH); //one way
  digitalWrite(DIRB, LOW);
}

void right() {
//  sensor();
  analogWrite(ENABLE_2, 125); // enable on

  // turn the left motor
  digitalWrite(DIRC, HIGH);  //one way
  digitalWrite(DIRD, LOW);
}

void Stop() {
//  sensor();
//  digitalWrite(ENABLE_1, LOW);
//  digitalWrite(ENABLE_2, LOW);
  analogWrite(ENABLE_1, 0); // enable on
  analogWrite(ENABLE_2, 0); // enable on
 
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  digitalWrite(DIRC, LOW);
  digitalWrite(DIRD, LOW);
}

void Fright() {
  right();
  forward();
}

void Fleft() {
  left();
  forward();
}

void Bleft() {
  left();
  back();
}

void Bright() {
  right();
  back();
}

void sensor() {
  distance = sr04.Distance();
  digitalWrite(led, LOW);
  if(distance < 30) {
    digitalWrite(led, HIGH);
  }
}
