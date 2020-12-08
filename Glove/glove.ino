
//for glove

#include <SoftwareSerial.h>

// for gyro
#include <GY6050.h>
#include <Wire.h>
             
 
int X = 0;
int Y = 0;
GY6050 gyro(0x68);                            // Create Gyro object with "0x68" as I2C addres (most likely the address of your MPU6050)

//SoftwareSerial BTserial(10, 11);


/*
 * BLUETOOTH (HC-05)
 * 
 */
 SoftwareSerial BluetoothSerial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// 
 
char c = ' ';



/**************************************************************************
 * SETUP()
 *************************************************************************/
void setup() {
 /************************************** 
  * GRYO setup 
  *************************************/
  gyro.initialisation();
  Serial.begin(9600);
  Serial.println("MPU6050 Test");
  delay(2500);

  /**************************************  
  * GLOVE setup
  *************************************/
//  Serial.begin(9600);
//  BTserial.begin(38400);
  
  Wire.begin();
//  gyro.initialisation();
  delay(2500);

  /**************************************  
  * BLUETOOH setup
  *************************************/
//  Serial.begin(9600);
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial monitor");
  
  // HC-05 default serial speed for AT mode is 38400
  BluetoothSerial.begin(38400);   
}

/*
 * LOOP()
 */
void loop() {
//  GRYO data
//  Serial.print("AcX = ");
//  Serial.print(gyro.refresh('A', 'X'));           // Ask for the X axis of the Accelerometer and print it
//  Serial.print(" | AcY = ");
//  Serial.print(gyro.refresh('A', 'Y'));           // Ask for the Y axis of the Accelerometer and print it
//  Serial.print(" | AcZ = ");
//  Serial.print(gyro.refresh('A', 'Z'));           // Ask for the Z axis of the Accelerometer and print it
//  Serial.print(" | Tmp = ");
//  Serial.print(gyro.refresh('T', 'C'));           // Ask for the Temperature in Celsius and print it
//  Serial.print(" C | ");
//  Serial.print(gyro.refresh('T', 'F'));           // Ask for the Temperature in Farenheit and print it
//  Serial.print(" F");
//  Serial.print(" | GyX = ");
//  Serial.print(gyro.refresh('G', 'X'));           // Ask for the X axis of the Gyroscope and print it
//  Serial.print(" | GyY = ");
//  Serial.print(gyro.refresh('G', 'Y'));           // Ask for the Y axis of the Gyroscope and print it
//  Serial.print(" | GyZ = ");
//  Serial.println(gyro.refresh('G', 'Z'));         // Ask for the Z axis of the Gyroscope and print it, then carriage return
  delay(25);
//  control GRYO data to movement for GLOVE
  X = gyro.refresh('A', 'X');
  Y= gyro.refresh('A', 'Y');
  
  if (X > -10 && X <  10 && Y > -10 && Y < 10)   { BluetoothSerial.write('S'); Serial.print(" Stop ");    }  
  if (X < -50 && Y > -10 && Y <  10)             { BluetoothSerial.write('F'); Serial.print(" Forward "); }  // Forward
  if (X >  50 && Y > -10 && Y <  10)             { BluetoothSerial.write('B'); Serial.print(" Back ");   }  // Backward
  if (Y < -50 && X > -10 && X <  10)             { BluetoothSerial.write('R'); Serial.print(" Right ");   }  // Right
  if (Y >  50 && X > -10 && X <  10)             { BluetoothSerial.write('L'); Serial.print(" Left ");    }  // Left
  if (Y < -50 && X < -30)                        { BluetoothSerial.write('N'); Serial.print(" RF ");    }   // Right + Forward 
  if (Y < -50 && X >  30)                        { BluetoothSerial.write('M'); Serial.print(" RB ");    }   // R + B
  if (Y >  50 && X < -30)                        { BluetoothSerial.write('O'); Serial.print(" LF ");    }   // L + F 
  if (Y >  50 && X >  40)                        { BluetoothSerial.write('P'); Serial.print(" LB ");    }   // L + B 

   
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BluetoothSerial.available())
  {  
    c = BluetoothSerial.read();
    Serial.write(c);
  }
  
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  {
    c =  Serial.read();
    BluetoothSerial.write(c);  
  }
}
