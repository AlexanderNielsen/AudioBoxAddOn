void InputSetup()
{
  Input1.begin();
  Input2.begin();
  Input3.begin();
  Input4.begin();
  Input5.begin();
  Input6.begin();
  Input7.begin();
  Input8.begin();
  
  // setting up configuration
  // default values are    RANGE_32V,         GAIN_8_320MV,       ADC_12BIT,        ADC_12BIT,          CONT_SH_BUS
  //   void configure(      range             gain                bus_adc           shunt_adc           mode;
  Input1.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input2.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input3.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input4.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input5.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input6.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input7.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input8.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);


  // calibrate with our values
  Input1.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Input2.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Input3.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Input4.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Input5.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Input6.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Input7.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Input8.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Wire.setClock(500000);
  Serial.println(F("*****INA219 Setup Done*****"));
}
