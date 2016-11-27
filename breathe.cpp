/*
Defines and function declarations

Emily Lam, November 2016
*/

#include "application.h"
#include <math.h>
#include "breathe.h"

// Determine breathing cycle based on icon field from Dark Sky
int detBreathePat(String value) {
  int breathePat;
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
  return breathePat;
}

// Set the breathing intensities
float setBreatheScale(int breathePat) {
  float breatheScale;
  if (breathePat == PCLOUDY || breathePat == CLOUDY) {
    breatheScale = (exp(sin(millis()/2000.0*3.1415)) - 0.36787944)*108.0; }
  else if (breathePat == RAIN || breathePat == SNOW || breathePat == SLEET) {
    breatheScale = 255; }
  else if (breathePat == WIND || breathePat == FOG) {
    breatheScale = 255; }
  else if (breathePat == NONE || breathePat == CLEAR) {
    breatheScale = 255; }
  else {breatheScale = 255; }
  return breatheScale;
}
