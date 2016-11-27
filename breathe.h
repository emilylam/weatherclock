/*
Defines and function declarations

Emily Lam, November 2016
*/

#ifndef _UTIL_H_
#define _UTIL_H_

// Icon/Pattern mapping
#define NONE    0
#define CLEAR   1
#define CLOUDY  2
#define RAIN    3
#define SNOW    4
#define SLEET   5
#define WIND    6
#define FOG     7
#define PCLOUDY 8

// Functions
int detBreathePat(String value);
float setBreatheScale(int breathePat);

#endif
