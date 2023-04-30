#include<Wire.h>
#include <SPI.h>
#include <SD.h>

// HDC1000 I2C address is 0x40(64)
#define Addr 0x40
#define analogPinForRV    1   // change to pins you the analog pins are using
#define analogPinForTMP   0

// to calibrate your sensor, put a glass over it, but the sensor should not be
// touching the desktop surface however.
// adjust the zeroWindAdjustment until your sensor reads about zero with the glass over it. 

const float zeroWindAdjustment =  .2; // negative numbers yield smaller wind speeds and vice versa.

int TMP_Therm_ADunits;  //temp termistor value from wind sensor
float RV_Wind_ADunits;    //RV output from wind sensor 
float RV_Wind_Volts;
unsigned long lastMillis;
int TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts;
float WindSpeed_MPH;
File myFile;

void setup()
{
// Initialise I2C communication as MASTER
Wire.begin();
// Initialise serial communication, set baud rate = 9600
Serial.begin(9600);
Serial.println("start");
  // put your setup code here, to run once:

  //   Uncomment the three lines below to reset the analog pins A2 & A3
  //   This is code from the Modern Device temp sensor (not required)
  pinMode(A2, INPUT);        // GND pin      
  pinMode(A3, INPUT);        // VCC pin
  digitalWrite(A3, LOW);     // turn off pullups
// Starts I2C communication
Wire.beginTransmission(Addr);
// Select configuration register
Wire.write(0x02);
// Temperature, humidity enabled, resolultion = 14-bits, heater on
Wire.write(0x30);
// Stop I2C Transmission
Wire.endTransmission();
delay(300);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");
}

void loop()
{
unsigned int data[2];
// Starts I2C communication
Wire.beginTransmission(Addr);
// Send temp measurement command
Wire.write((byte)0x00);
// Stop I2C Transmission
Wire.endTransmission();
delay(500);

// Request 2 bytes of data
Wire.requestFrom(Addr, 2);

// Read 2 bytes of data
// temp msb, temp lsb
if (Wire.available() == 2)
{
data[0] = Wire.read();
data[1] = Wire.read();
}
// Convert the data
int temp = (data[0] * 256) + data[1];
float cTemp = (temp / 65536.0) * 165.0 - 40;
float fTemp = cTemp * 1.8 + 32;

// Starts I2C communication
Wire.beginTransmission(Addr);
// Send humidity measurement command
Wire.write(0x01);
// Stop I2C Transmission
Wire.endTransmission();
delay(500);

// Request 2 bytes of data
Wire.requestFrom(Addr, 2);

// Read 2 bytes of data
// humidity msb, humidity lsb
if (Wire.available() == 2)
{
data[0] = Wire.read();
data[1] = Wire.read();
}

// Convert the data
float humidity = (data[0] * 256) + data[1];
humidity = (humidity / 65536.0) * 100.0;

// Output data to serial monitor
Serial.print("Relative Humidity :");
Serial.print(humidity);
Serial.println(" %RH");
Serial.print("Temperature in Celsius :");
Serial.print(cTemp);
Serial.println(" C");
Serial.print("Temperature in Fahrenheit :");
Serial.print(fTemp);
Serial.println(" F");
delay(5000);
if (millis() - lastMillis > 5000){      // read every 200 ms - printing slows this down further
    
    TMP_Therm_ADunits = analogRead(analogPinForTMP);
    RV_Wind_ADunits = analogRead(analogPinForRV);
    RV_Wind_Volts = (RV_Wind_ADunits *  0.0048828125);

    // these are all derived from regressions from raw data as such they depend on a lot of experimental factors
    // such as accuracy of temp sensors, and voltage at the actual wind sensor, (wire losses) which were unaccouted for.
    TempCtimes100 = (0.005 *((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4;  

    zeroWind_ADunits = -0.0006*((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172;  //  13.0C  553  482.39

    zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment;  

    // This from a regression from data in the form of 
    // Vraw = V0 + b * WindSpeed ^ c
    // V0 is zero wind at a particular temperature
    // The constants b and c were determined by some Excel wrangling with the solver.
    
   WindSpeed_MPH =  pow(((RV_Wind_Volts - zeroWind_volts) /.2300) , 2.7265);   
   
    /*Serial.print("  TMP volts ");
    Serial.print(TMP_Therm_ADunits * 0.0048828125);
    
    Serial.print(" RV volts ");
    Serial.print((float)RV_Wind_Volts);

    Serial.print("\t  TempC*100 ");
    Serial.print(TempCtimes100 );

    Serial.print("   ZeroWind volts ");
    Serial.print(zeroWind_volts);*/

    Serial.print("WindSpeed MPH ");
    Serial.println((float)WindSpeed_MPH);
    myFile = SD.open("weather.csv", FILE_WRITE);
    if (myFile) {
      String dataString = "";
      dataString += String(humidity);
      dataString += ",";
      dataString += String(fTemp);
      dataString += ",";
      dataString += String(WindSpeed_MPH);
      Serial.print("Writing to file");
      myFile.println(dataString);
      myFile.close();
      Serial.println("Done.");
    } else {
      Serial.println("Error opening file.");
    }
    
    lastMillis = millis();   
} 
}
