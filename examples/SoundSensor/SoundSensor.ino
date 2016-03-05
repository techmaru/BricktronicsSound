// Bricktronics Example: SoundSensor
// http://www.wayneandlayne.com/bricktronics
// This example uses a LEGO NXT Sound Sensor.
//
// Sound sensor readings are as fast a possible and used to generate a
// simple bar graph printed out over the serial console. Be sure to set
// your serial console to 115200 baud. The sound sensor library reports the
// measured sound value with a unitless value between 0 (very quiet) and
// 1023 (very loud).
//
// The sound sensor is described by LEGO as a "sound pressure level" sensor,
// that has two modes: dB and dBA. dB mode measures all frequencies equally,
// while dBA mode (A = "adjusted") tries to mimic human ear sensitivity, by
// ignoring frequencies outside the normal limits of human hearing.
//
// Written in 2015 by Matthew Beckler and Adam Wolf for Wayne and Layne, LLC
// To the extent possible under law, the author(s) have dedicated all
//   copyright and related and neighboring rights to this software to the
//   public domain worldwide. This software is distributed without any warranty.
// You should have received a copy of the CC0 Public Domain Dedication along
//   with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 


// Include the BricktronicsSound library
#include <BricktronicsSound.h>


// This example can be run in three different ways. Pick one, and un-comment
// the code lines corresponding to your chosen method. Comment-out the lines
// for the other methods that you aren't using.

// 1. With a Bricktronics Shield - Include these lines and be sure to
// call BricktronicsShield::begin() in the setup() function below.
// You also need to install the Adafruit MCP23017 library:
//	https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
// Select the sensor port for the sound sensor (SENSOR_1 through SENSOR_4) below.
// For ports 3 and 4, use the jumpers to connect pins 2-3 and 4-5.
//
// Config 1 - CFG_WNL_BS
//#include <Wire.h>
//#include <Adafruit_MCP23017.h>
//#include <BricktronicsShield.h>
//BricktronicsSound s(BricktronicsShield::SENSOR_1);
// Config end

// 2. With a Bricktronics Megashield - Include these lines but do not
// call BricktronicsShield::begin() in the setup() function below.
// Select the sensor port for the sound sensor (SENSOR_1 through SENSOR_4) below.
// Use the jumpers to connect pins 2-3 and 4-5 for the sound sensor.
//
// Config 2 - CFG_WNL_BMS
//#include <BricktronicsMegashield.h>
//BricktronicsSound s(BricktronicsMegashield::SENSOR_4);
// Config end

// 3. With a Bricktronics Breakout board - No additional includes needed, just
// update the pin assignments in the SoundSensor constructor below.
//
// Connect these pins on the Bricktronics Breakout board:
//  Pin 1 - Connect to any analog input pin (inputPin)
//  Pin 2 - Connect to Ground
//  Pin 3 - Connect to Ground
//  Pin 4 - Connect to 5V
//  Pin 5 - Connect to any digital pin (dbPin)
//  Pin 6 - Connect to any digital pin (dbaPin)
//
// The BricktronicsSound() arguments are:
//      inputPin (pin 1), dbPin (pin 5), dbaPin (pin 6)
// There is one consideration for pin assignments:
// A. inputPin needs to be an analog pin
//
// Config 3 - CFG_WNL_NS
//BricktronicsSound s(14, 12, 11);
// Config end


void setup()
{
  // Be sure to set your serial console to 115200 baud
  Serial.begin(115200);

  // Only call this if you are using a Bricktronics Shield,
  // otherwise leave it commented-out.
  // Config 1 - CFG_WNL_BS
  //BricktronicsShield::begin();
  // Config end

  // Initialize the sound sensor connections
  s.begin();
}

// This function draws a nice bar graph for displaying sound levels.
void printLine(uint16_t val, char dot)
{
  #define BUF_LEN 30
  char buffer[BUF_LEN];
  uint8_t x = (val * (uint16_t) BUF_LEN) / 1023;
  for (uint8_t i = 0; i < BUF_LEN; i++)
  {
    buffer[i] = ((i < x) ? dot : ' ');
  }
  buffer[BUF_LEN - 1] = '\0';
  Serial.println(buffer);
}

long switchTime;

void loop()
{
  // Spend 5 seconds in db mode
  Serial.println("----- Switching to DB mode -----");
  s.setMode(SOUND_SENSOR_MODE_DB);
  switchTime = millis() + 5000;
  while (millis() < switchTime)
  {
    printLine(s.value(), '*');
  }

  // Spend 5 seconds in dba mode
  Serial.println("----- Switching to DBA mode -----");
  s.setMode(SOUND_SENSOR_MODE_DBA);
  switchTime = millis() + 5000;
  while (millis() < switchTime)
  {
    printLine(s.value(), 'a');
  }
}

