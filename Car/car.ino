int E1 = 10;  //left wheel
int M1 = 12; //left wheel
int E2 = 11;  //right wheel
int M2 = 13;  //right wheel
void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}
void loop()
{

  //makes the car go backwards.
  { int value;
    for (value = 0 ; value <= 255; value += 5)
    {
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
      analogWrite(E1, value);
      analogWrite(E2, value);
      delay(30);
    }

    delay(1000); // dont mess with this
  }
  //makes the car go forward
  { int value;
    for (value = 0 ; value <= 255; value += 5)
    {
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      analogWrite(E1, value);
      analogWrite(E2, value);
      delay(30); // duration of the rotation of the wheel
    }
    delay(1000);
  }
}

