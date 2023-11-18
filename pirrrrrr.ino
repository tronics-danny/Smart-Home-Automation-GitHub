int PIR1 = 7;
int PIR2 = 3;
int PIR3 = 4;
int PIR4 = 5;
int PIR5 = 6;
int relay1 = 2;
int relay2 = 8;
int relay3 = 9;
int relay4 = 10;
int relay5 = 11;

void setup()
{
  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);
  pinMode(PIR3, INPUT);
  pinMode(PIR4, INPUT);
  pinMode(PIR5, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
}

void loop()
{
  backyard();
  living_room();
  bedroom();
  kitchen();
  washroom();
}

void backyard()
{
  int value1 = digitalRead(PIR1);
  if (value1 == HIGH)
  {
    digitalWrite(relay1, HIGH);
    delay(5000);
  }
  else
  {
    digitalWrite(relay1, LOW);
  }
}
  
void living_room()
{
  int value2 = digitalRead(PIR2);
  if (value2 == HIGH)
  {
    digitalWrite(relay2, HIGH);
    delay(5000);
  }
  else
  {
    digitalWrite(relay2, LOW);
  }
}

void bedroom()
{
  int value3 = digitalRead(PIR3);
  if (value3 == HIGH)
  {
    digitalWrite(relay3, HIGH);
    delay(5000);
  }
  else
  {
    digitalWrite(relay3, LOW);
  }
}
  
void kitchen()
{
  int value4 = digitalRead(PIR4);
  if (value4 == HIGH)
  {
    digitalWrite(relay4, HIGH);
    delay(5000);
  }
  else
  {
    digitalWrite(relay4, LOW);
  }
}

void washroom()
{
  int value5 = digitalRead(PIR5);
  if (value5 == HIGH)
  {
    digitalWrite(relay5, HIGH);
    delay(5000);
  }
  else
  {
    digitalWrite(relay5, LOW);
  }
}
  