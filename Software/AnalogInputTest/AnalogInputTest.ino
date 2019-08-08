#include <Wire.h>
#include <INA219.h>
#define SHUNT_MAX_V 0.32  // Rated max for our shunt is 75mv for 50 A current:
#define BUS_MAX_V   16.0  // with 12v lead acid battery this should be enough
#define MAX_CURRENT 0.15  // In our case this is enaugh even shunt is capable to 50 A
#define SHUNT_R    1.21  // Shunt resistor in ohm

INA219 Input1(0x4A);
INA219 Input2(0x4F);
INA219 Input3(0x49);
INA219 Input4(0x4E);
INA219 Input5(0x46);
INA219 Input6(0x4B);
INA219 Input7(0x45);
INA219 Input8(0x48);

void setup() {
  Input1.begin();
  Input1.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input1.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Serial.begin(115200);
}

void loop() {
  Serial.println(abs(Input1.shuntCurrent() * 1000));
}
