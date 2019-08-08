void MenuLogic()
{

  // changes values if encoder SW is NOT pressed and system is NOT armed.
  if (swState == HIGH and menu != 3)
  { // determins where to add the difference


    if (pressVal == 1)
    {
      pressVal = 0;

      if (col == 0)
      {
        col++;
      }
      else
      {
        col = 0;
      }

    }

    if (col == 0)
    {
      row += encDiff;
      row = constrain(row, 0, 1);
    }
    else
    {
      // if
      if (encDiff >= 0)
      {
        encDiff = encDiff * encDiff;
      }
      else
      {
        encDiff = (encDiff * encDiff) * -1;
      }
      values[row][0] += encDiff * values[row][3];
      values[row][0] = constrain(values[row][0], values[row][1], values[row][2]);
    }
    Serial.print("encDiff:");
    Serial.print(encDiff);
    encDiff = 0;


    Serial.print("Values: ");
    for (int c = 0; c < 4; c++)
    {
      for (int r = 0; r < 1; r++)
      {
        Serial.print(values[r][c]);
        Serial.print("\t");
      }
    }
    Serial.print(col);
    Serial.print("\t");
    Serial.println(row);

    /*
        // maps row and col-map
        rowMap = constrain(rowMap, 0, 6);
        colMap = constrain(colMap, 0, 4);


        switch (rowMap)
        {
          case 0: row = 0; break;
          case 2: row = 1; break;

        };
    */
    UpdateDisplay();
  }
}





void UpdateDisplay()
{
  // if menu different from last update clear screen
  if (menu != menuLast)
  {
    lcd.clear();

    switch (menu)
    {
      case 0: // if menu changed back to 0 reset menu and show only seleced state
        //        state       = 0;    // reset state
        col         = 0;    // reset col
        colMap      = 0;    // reset colmap since it is used to calculate col.
        break;

      case 1:
        //   redrawCont  = 1;    // forces the continuity function to draw all at first runtrue
        break;

      case 3: // if menu changed back to 0 reset menu and show only seleced state
        //   state       = 0;    // reset state
        col         = 0;    // reset col
        colMap      = 0;    // reset colmap since it is used to calculate col.
        break;
    }
    menuLast = menu;  // save new menu level as the lastmenu
  }

  // determin which menu to draw on the lcd
  switch (menu) {
    case 0: MainMenu();         break;
    case 1: USBMenu();          break;
    case 2: PowerOffWarning();  break;
  }

}
