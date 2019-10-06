/*
** ERMPUNO
**
*/

int pot1 = A0;

int led1 = 3;
int led2 = 5;
int ledstatus = 13;

int pot1value = 0;   

int ramp=0;
int de=1000;
int mode = 0;
int first = 1;

int calibrate = 0;

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(ledstatus, OUTPUT);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(ledstatus, LOW);
}

void loop() {
  pot1value = analogRead(pot1);
  //pot2value = analogRead(pot2);

  if (pot1value < 50)
  {
    de = 250;
    mode = 1;
  }
  else if (pot1value < 400)
  {
    de = 500;
    mode = 2;
  }
  else if (pot1value < 600)
  {
    de = 750;
    mode = 3;
  }
  else if (pot1value < 750)
  {
    de = 1000;
    mode = 4;
  }
  else if (pot1value < 875)
  {
    de = 1500;
    mode = 5;
  }
  else if (pot1value < 1000)
  {
    de = 2000;
    mode = 6;
  }
  else
  {
    de = 3000;
    mode = 7;
  }

  if (calibrate)
  {
    Serial.print(de);
    Serial.print("   ");
    Serial.print(mode);
    Serial.print("   ");
    Serial.print(pot1value);
    Serial.println();
  }
  
  if (ramp == 0)
  {
    digitalWrite(led2, LOW);
    digitalWrite(led1, HIGH);
  }
  else
  {
    for (int i=0; i<255; i++)
    {
      analogWrite(led1,i);
      if (first != 1)
      {    
        analogWrite(led2,255-i);
      }
      delay(ramp);
    }
  }
  first = 0;

  delay(de);

  if (calibrate)
  {
    Serial.print(de);
    Serial.print("   ");
    Serial.print(mode);
    Serial.print("   ");
    Serial.print(pot1value);
    Serial.println();
  }
  
  if (ramp == 0)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
  }
  else
  {
    for (int i=255; i>=0; i--)
    {
      analogWrite(led1,i);
      analogWrite(led2,255-i);
      delay(ramp);
    }
  }

  delay(de);
}
