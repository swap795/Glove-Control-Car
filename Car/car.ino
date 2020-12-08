#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);

SoftwareSerial BluetoothSerial(2, 3); // RX | TX

#define ENABLE_1 10
#define ENABLE_2 11

#define DIRA 8
#define DIRB 9
#define DIRC 12
#define DIRD 13

int state = 0;

void setup() {
  Serial.begin(9600);
  BTserial.begin(38400);

  pinMode(ENABLE_1, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(DIRC, OUTPUT);
  pinMode(DIRD, OUTPUT);

//  bluetooth
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
 
  // HC-06 default baud rate is 9600
  BluetoothSerial.begin(9600);  
}

void loop() {
  if (BluetoothSerial.available() > 0) { 
    state = BluetoothSerial.read();
    
    Stop();
    
    switch(state) {
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


  /*
   * Bluetooth
   */
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (BluetoothSerial.available()) {
    Serial.write(BluetoothSerial.read());
  }
      
  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available()) {
    BluetoothSerial.write(Serial.read());
  }

}


  
void forward() {
//  analogWrite(E1, 153); // Run in half speed
//  analogWrite(E2, 255); // Run in full speed
  
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
}

void back() {
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
}

void left() {
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,HIGH); 
}

void right() {
  digitalWrite(DIRD,LOW);
  digitalWrite(DIRC,HIGH);
}

void Stop() {
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,LOW);
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
