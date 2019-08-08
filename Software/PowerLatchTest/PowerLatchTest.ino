int buttonRead = A7;
int buttonOff = 3;
int buttonVal = 0;

int powerOff = 0;

void setup() {
  pinMode(buttonRead, INPUT_PULLUP);
  pinMode(buttonOff, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buttonOff, HIGH);
}

void loop()
{

  buttonVal = analogRead(buttonRead);


  if (buttonVal > 512)
  {
    powerOff = 1;
  }


  if (powerOff == 1)
  {
    Serial.println("Off warning");
    delay(1000);
    digitalWrite(buttonOff, LOW);
    powerOff = 0;

  }
  else
  {
    Serial.println(buttonVal);
    digitalWrite(buttonOff, HIGH);
  }
}
