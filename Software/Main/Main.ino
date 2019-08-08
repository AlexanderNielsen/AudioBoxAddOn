//--------------------------------------------------------------------------------
//INA219 analog input vaiables
#include <Wire.h>
#include <INA219.h>
#define SHUNT_MAX_V 0.32  // Rated max for our shunt is 75mv for 50 A current:
#define BUS_MAX_V   16.0  // with 12v lead acid battery this should be enough
#define MAX_CURRENT 0.15  // In our case this is enaugh even shunt is capable to 50 A
#define SHUNT_R    1.21  // Shunt resistor in ohm

// INA219 addresses
INA219 Input1(0x4A);
INA219 Input2(0x4F);
INA219 Input3(0x49);
INA219 Input4(0x4E);
INA219 Input5(0x46);
INA219 Input6(0x4B);
INA219 Input7(0x45);
INA219 Input8(0x48);

const byte inputBufferSize = 4;
int inputData[4][inputBufferSize];
int inputLimit = 180; // 180mA trip value -> enables trigger by 9v battery (22ohm*0.180mA=3,96)

long TMin  = 100000;
long TMax  = 0;
long TMeas = 0;
long TSum  = 0;


//--------------------------------------------------------------------------------
// DMX variables
#include <DmxSimple.h>
const int DMXChannels = 7;
const int DMXArmVal = 150;
const int DMXPin = 9;


//--------------------------------------------------------------------------------
//Encoder and SW variable
#include <Encoder.h>
Encoder myEnc(2, 3);
// encoder Variables
long oldPosition  = 0;        // old position of the encoder
int encDiff;                  // difference between last and current value of encoder

// Switch variables
unsigned long PressTime = 0;  // time from when the switch was pressed
char swState = 1;             // current state of switch
char swStateLast = 1;         // last known state of switch
const char pressLimit = 40;   // debounce time for switch press
const int holdTime = 2500;    // time limit for a hold press
char pressVal = 0;            // 0=ingen,1=short,2=long,3=hold,4=double
const char swPin = 4;         // physical pin of switch


//--------------------------------------------------------------------------------
//MainMenu variables
unsigned int armStatus         =     0;    // saves the status of the arm LED in the 18R2 remote
unsigned int batteryVoltage    =     0;    // saved as a 10x value to keep as a integer
unsigned int flameoffDelay     =     5;    // time the flame is held on for.
unsigned int flameOnInterval   =    50;    // scaling used in the menu to determind the intervals in ms
unsigned int flameOnMax        =  5000;    // maximum on Time for flames in ms
unsigned int antenneBoost      =     0;    // used to turn on the AntennaBooster.

int values[2][4]={
                 {250,0,5000,50},
                 {0,0,   1,1}};

int armPin      = A6;
int batteryPin  = A7;


//--------------------------------------------------------------------------------
// menu logic variables
int row       = 0;    // selected row   Change between the 2 settings
int col       = 0;    // selected collume used for change between items or values.
int rowMap    = 0;    //  used to map 2 vertical steps into "row"
int colMap    = 0;    //  used to map 2 horizontal steps into "col"

byte  menu    = 0;    // 0 = MainMenu 1 = PowerOff 2 = BatteryWarning  3 = Armed  4= Disarme.
byte menuLast = 0;


//--------------------------------------------------------------------------------
// LCD setup and variables
#include <LCD.h>
#include <LiquidCrystal_SR3W.h>
//LiquidCrystal_SR lcd(6, 8, 7);       // dat clk enable
//LiquidCrystal pins  (da,clk,en,En, Rw, Rs, d4, d5, d6, d7,BL, POSITIVE);
LiquidCrystal_SR3W lcd(6,  8, 7,  1,  0,  2,  3,  4,  5,  6, 7, POSITIVE);


void setup() {
  // Input setup
  Input1.begin();
  Input1.configure(INA219::RANGE_32V, INA219::GAIN_8_320MV, INA219::ADC_9BIT, INA219::ADC_12BIT, INA219::CONT_SH);
  Input1.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  Wire.setClock(400000);
  //InputSetup();     //Analoginput setup 8x INA219 chips

  // Serial setup
  Serial.begin(115200);
  Serial.println("Time\tTMin\tTMax\tGns\tData[1]");

  // DMX setup
  DmxSimple.usePin(DMXPin);
  DmxSimple.maxChannel(DMXChannels);

  LCDSetup();
}
void loop()
{
  ReadEncoder();

  armStatus = analogRead(armPin);
  int batteryRaw =   analogRead(batteryPin);
  batteryVoltage = long (batteryRaw) * 250 / 1023;







}
void inputTest()
{
  int Data[11], DataSum;
  unsigned long Time1, Time2;
  DmxSimple.write(17, 0);
  Time1 = micros();

  Data[1] = Input1.shuntCurrent() * 10000;
  Data[2] = Input1.shuntCurrent() * 10000;
  Data[3] = Input1.shuntCurrent() * 10000;
  Data[4] = Input1.shuntCurrent() * 10000;
  Data[5] = Input1.shuntCurrent() * 10000;
  Data[6] = Input1.shuntCurrent() * 10000;
  Data[7] = Input1.shuntCurrent() * 10000;
  Data[8] = Input1.shuntCurrent() * 10000;
  Data[9] = Input1.shuntCurrent() * 10000;
  Data[10] = Input1.shuntCurrent() * 10000;
  Data[11] = Input1.shuntCurrent() * 10000;
  Data[12] = Input1.shuntCurrent() * 10000;
  Data[13] = Input1.shuntCurrent() * 10000;
  Data[14] = Input1.shuntCurrent() * 10000;
  Data[15] = Input1.shuntCurrent() * 10000;
  Data[16] = Input1.shuntCurrent() * 10000;

  for (int i = 1; i <= 16; i++)
  {
    if (Data[i] > inputLimit)
    {
      DmxSimple.write(i, 255);
    }
    else
    {
      DmxSimple.write(i, 0);
    }
  }

  Time2 = micros();
  long TDelta = Time2 - Time1;
  if ((TDelta) > TMax)
  {
    TMax = TDelta;
  }
  if (TDelta < TMin)
  {
    TMin = TDelta;
  }

  DataSum = 0;
  for (int i = 1; i <= 16; i++)
  {
    DataSum += Data[i];
  }

  TSum += TDelta;

  TMeas++;

  /*
    Serial.print(TDelta);

    Serial.print("\t");
    Serial.print(TMin);

    Serial.print("\t");
    Serial.print(TMax);

    Serial.print("\t");
    Serial.print(TSum / TMeas);

    Serial.print("\t");
    Serial.println(Data[1]);
  */
}
