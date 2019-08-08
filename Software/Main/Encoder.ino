void ReadEncoder()
{
  long newPosition = myEnc.read()/4;
  if (newPosition != 0)
  {
    encDiff = newPosition;

    myEnc.write(0);
  }
  ReadSwitch();
  MenuLogic();
}

// reads the switch and determind if it is a short press or a long hold.
void ReadSwitch()
{
  if (menu != 3)
  {
    swState = digitalRead(swPin);

    // Switch Pressed
    if (swState != swStateLast && swState == LOW )
    {
      PressTime = millis();
      pressVal = 0;
    }

    // Switch released
    if (swState == HIGH && swState != swStateLast && pressVal != 3)
    {
      // short press if...
      if ((millis() - PressTime) > pressLimit and (millis() -

          PressTime < holdTime) and menu != 1)
      {
        pressVal = 1;
        Serial.println(F("Short press"));
        UpdateDisplay();
      }
    }
    // hold funktion if ...
    if ((millis() - PressTime) > holdTime && swState == LOW && pressVal != 3)
    {
      pressVal = 3;
      Serial.println(F("Hold press Change to USB:"));
      menu++;
      menu = menu % 2;
      UpdateDisplay();
    }
    else if ( pressVal == 3)
    {
      PressTime = millis();
    }
    swStateLast = swState;
  }
}
