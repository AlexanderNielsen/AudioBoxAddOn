void LCDSetup()
{
  pinMode(5, OUTPUT);
  analogWrite(5, 1);
  lcd.setBacklight(HIGH);
  lcd.begin(20, 4);
  lcd.home();


  lcd.noBlink();
  lcd.noCursor();
  lcd.clear();
  Serial.println(F("*****LCD Setup Done*****"));
}





void MainMenu()
{

  // prints ArmStatus
  lcd.setCursor(0, 0);  // place cursor(x,y)
  if (armStatus == 0)
  {
    lcd.print(F("Safe "));
  }
  else
  {
    lcd.print(F("Armed"));
  }

  // Print Battery Voltage
  lcd.setCursor(12, 0);
  // if voltage is under 10V add a space to prevent offset.
  if (batteryVoltage < 100)
  {
    lcd.print(F(" "));
  }
  lcd.print((float(batteryVoltage) / 10), 1);
  lcd.print(F("V"));

  // print settings:
  lcd.setCursor(0, 2);
  lcd.print(F("Flame On Time:"));


  // prints the time the flames are held on
  //float Time = (float)flameoffDelay * flameOnInterval / 1000; // calcuates on Time
  
   float Time = (float)values[0][0] / 1000; // calcuates on Time
  lcd.setCursor(14, 2);                 // sets cursor
  if (Time < 10)                                    // if less than 10 padd with a  space
  {
    lcd.print(F(" "));
  }
  lcd.print(float(Time), 2);    // print On time
  lcd.print(F("S"));



  lcd.setCursor(0, 3);
  lcd.print(F("Antenne Boost:"));

  if (values[1][0] == 0)
  {
    lcd.print(F(" OFF"));
  }
  else
  {
    lcd.print(F(" ON "));
  }

}

void USBMenu()
{
  lcd.setCursor(1, 0);
  lcd.print(F("External USB Mode:"));

  lcd.setCursor(0, 1);
  lcd.print(F("Script Transferring"));
  
  lcd.setCursor(0, 3);
  lcd.print(F("Release ! to return"));
}

void PowerOffWarning()
{

  lcd.setCursor(5, 0);
  lcd.print(F("Warning!"));

  lcd.setCursor(0, 1);
  lcd.print(F("Power Switch flipped"));

  lcd.setCursor(0, 2);
  lcd.print(F("Press  and hold "));

  lcd.setCursor(0, 3);
  lcd.print(F("to confirm Shutdown"));
}
