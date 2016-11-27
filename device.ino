/*
Weather clock photon code
Processes weather data and displays it using RGB LEDs

Emily Lam, November 2016
*/

#include <math.h>
#include "util.h"

// Variables
int testled = D7;
float floatTemp = 0;
int r,g,b = 0;
int rval,gval,bval;
int breathePat = NONE;
float breatheScale = 255;

// Setup loop
void setup() {
  Serial.begin(9600);
  pinMode(testled, OUTPUT);
  digitalWrite(testled, LOW);
  Particle.function("temp", procTemp);
  Particle.function("icon", procIcon);
  RGB.control(true);
  delay(1000);
}

// Main loop
void loop() {
  setBreatheScale(breathePat);
  RGB.color(rval, gval, bval);
}

// Process temperature received
int procTemp(String rcvTemp) {
  //float test = -5.34;
  Serial.println(rcvTemp);
  floatTemp = rcvTemp.toFloat();
  calcRGBvalue(floatTemp);
  return 1;
}

// Process icon received
int procIcon(String rcvIcon) {
  Serial.println(rcvIcon);
  detBreathePat(rcvIcon);
  return 1;
}

// Convert temperature to RGB value
void calcRGBvalue(float value) {
  if (value > 100) { value = 100; }
  else if (value < 0) { value = 0; }
  float f = value/100;
  float a = (1-f)/0.2;
  int X = floor(a);
  int Y = floor(255*(a-X));
  Serial.print("Temp: ");
  Serial.println(value);
  Serial.print("a: ");
  Serial.println(a);
  Serial.print("X: ");
  Serial.println(X);
  Serial.print("Y: ");
  Serial.println(Y);

  switch(X)
  {
    case 0: r = 255; g = Y; b = 0; break;
    case 1: r = 255-Y; g = 255; b = 0; break;
    case 2: r = 0; g = 255; b = Y; break;
    case 3: r = 0; g = 255-Y; b = 255; break;
    case 4: r = Y; g = 0; b = 255; break;
    case 5: r = 255; g = 0; b = 255; break;
    default: r = 0; g = 0; b = 0; break;
  }
}

// Determine breathing cycle based on icon field from Dark Sky
void detBreathePat(String value) {
  if (value == "\"partly-cloudy-night\"" || "\"partly-cloudy-day\"") {
    breathePat = PCLOUDY; }
  else if (value == "\"clear-day\"" || value == "\"clear-night\"") {
    breathePat = CLEAR; }
  else if (value == "\"rain\"") { breathePat = RAIN; }
  else if (value == "\"snow\"") { breathePat = SNOW; }
  else if (value == "\"sleet\"") { breathePat = SLEET; }
  else if (value == "\"wind\"") { breathePat = WIND; }
  else if (value == "\"fog\"") { breathePat = FOG; }
  else if (value == "\"cloudy\"") { breathePat = CLOUDY; }
  else { breathePat = NONE; }
  Serial.print("Pattern: ");
  Serial.println(breathePat);
}

// Set the breathing intensities
void setBreatheScale(int breathePat) {
  if (breathePat == PCLOUDY || breathePat == CLOUDY) {
    breatheScale = (exp(sin(millis()/2000.0*3.1415)) - 0.36787944)*108.0; }
  else if (breathePat == RAIN || breathePat == SNOW || breathePat == SLEET) {
    breatheScale = 255; }
  else if (breathePat == WIND || breathePat == FOG) {
    breatheScale = 255; }
  else if (breathePat == NONE || breathePat == CLEAR) {
    breatheScale = 255; }
  else {breatheScale = 255; }

  rval = round(breatheScale * (r/ (float) 255));
  gval = round(breatheScale * (g/ (float) 255));
  bval = round(breatheScale * (b/ (float) 255));
}
